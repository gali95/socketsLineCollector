/*
 * LineSharingServer.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __linux__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#elif _WIN32

#include "../Stubs/LinuxSockets.h"

#endif

#include <pthread.h>

#include "LineSharingServer.h"
#include "../Log/Logger.h"
#include "ConnectionArguments.h"
#include "Capabilities/BasicCapabilitiesImpl/SendAvailableLineCapability.h"
#include "Capabilities/BasicCapabilitiesImpl/SendAvailableLineNumberCapability.h"
#include "../CollectedData/DiscoveredApplicationsInfo/DiscoveredApplications.h"

LineSharingServer::LineSharingServer(int startPort,int endPort):
m_port(startPort),
m_startPort(startPort),
m_endPort(endPort),
m_clientConnectionIdCounter(1),
m_stopServer(false),
m_serverStarted(false)
{
	AddCapability(new SendAvailableLineCapability());
	AddCapability(new SendAvailableLineNumberCapability());
}

LineSharingServer::~LineSharingServer()
{
	for(StringCapability *cap : m_capabilities)
	{
		delete cap;
	}
}

void* LineSharingServer::StartServer()
{

	if(m_serverStarted || m_stopServer)
	{
		pthread_exit(NULL);
	}

	m_serverStarted = true;
	bool m_connectionSuccessfull = false;

	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	do
	{
		sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
		if (sockfd < 0)
		{
			Logger::GetLogger()->Log({"error"},"ERROR opening socket");
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		portno = m_port;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if (bind(sockfd, (struct sockaddr *) &serv_addr,
				 sizeof(serv_addr)) < 0)
		{
			Logger::GetLogger()->Log({"error"},"ERROR on binding on port ");
		}
		else
		{
			m_connectionSuccessfull = true;
			break;
		}

	} while (NextPort());

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

    while(m_connectionSuccessfull && !m_stopServer)
    {
        newsockfd = accept(sockfd,
                    (struct sockaddr *) &cli_addr,
                    &clilen);
        if (newsockfd >= 0)
        {
        	Logger::GetLogger()->Log({"connection" , "server"}," Connection incoming from client");

        	sockaddr_in clientAdress = static_cast<sockaddr_in>(cli_addr);
        	m_connectedClientsIPs[newsockfd] = inet_ntoa(clientAdress.sin_addr);

        	m_connectionThreads.push_back(new pthread_t());

        	ConnectionArguments *connArgs = new ConnectionArguments(this, newsockfd);

        	pthread_attr_init(&m_serverAttr);
        	pthread_attr_setdetachstate(&m_serverAttr, PTHREAD_CREATE_JOINABLE);

        	int pthreadResult = pthread_create(m_connectionThreads.back(), NULL, &LineSharingServer::ConnectionPthreadFacade, connArgs);
        	if(pthreadResult)
        	{
        		Logger::GetLogger()->Log({"error"},"Error: failed to create server thread");
        	}
        }
        else
        {
        	Logger::GetLogger()->Log({"error" , "server"}, (string)"ERROR on accept " + to_string(newsockfd));
        }
        sleep(1);
    }

    if(m_connectionSuccessfull)
    {
    	WaitForConnectionsToClose();
    }

    close(sockfd);
    Logger::GetLogger()->Log({"info"},"LineSharingServer::startServer() finished");
    pthread_exit(NULL);
}

void* LineSharingServer::Connection(int newsockfd) {

	char buffer[256];
	double timeToCloseConnection = TIME_WITHOUT_REQUESTS_TO_CLOSE_SOCKET_CONNECTION;
	int n;
	m_discoveredClientDataSend = false;

	while(timeToCloseConnection > 0)
	{
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0)
		{
			Logger::GetLogger()->Log({"error"},"ERROR reading from socket");
			timeToCloseConnection -= WAIT_FOR_REQUEST_INTERVAL;
			sleep(WAIT_FOR_REQUEST_INTERVAL);
		}
		else if (n > 0)
		{
			Logger::GetLogger()->Log({"server","socket_read"},(string)buffer +
					" port:" + to_string(m_port) +
					" odebrane bajty: " + to_string(n));
			string requestResponse = CreateResponseForClientRequest(buffer);
			if(requestResponse != "")
			{
				bzero(buffer,256);
				n = write(newsockfd,requestResponse.c_str(),requestResponse.length());
				if (n < 0)
				{
					Logger::GetLogger()->Log({"error"},"ERROR writing to socket");
				}
				else
				{
					Logger::GetLogger()->Log({"server","socket_write"},requestResponse +
							" port:" + to_string(m_port) +
							" wyslane bajty: " + to_string(n));
				}
				timeToCloseConnection = TIME_WITHOUT_REQUESTS_TO_CLOSE_SOCKET_CONNECTION;
			}

		}
		if(m_stopServer)
		{
			break;
		}
	}

	if(timeToCloseConnection <= 0)
	{
		SendDiscoveredClientData(m_connectedClientsIPs[newsockfd],false);
	}

	m_connectedClientsIPs.erase(newsockfd);
	close(newsockfd);

	pthread_exit(NULL);
}

void* LineSharingServer::StartServerPthreadFacade(
		void* LineSharingServerPointer) {

	return ((LineSharingServer *)LineSharingServerPointer)->StartServer();

}

void* LineSharingServer::ConnectionPthreadFacade(
		void* LineSharingServerPointer) {

	ConnectionArguments arguments = *(reinterpret_cast<ConnectionArguments*>(LineSharingServerPointer));

	return (arguments.m_server)->Connection(arguments.m_newsockfd);
}

void LineSharingServer::StopServer() {

    if(!m_serverStarted || m_stopServer)
    {
    	return;
    }

	m_stopServer = true;
}

string LineSharingServer::CreateResponseForClientRequest(string request) {

	string response = "";

	for(vector<StringCapability*>::iterator capIt = m_capabilities.begin(); capIt != m_capabilities.end() ; ++capIt)
	{
		if((*capIt)->CanHandleString(request))
		{
			response = (*capIt)->HandleString(request);
			Logger::GetLogger()->Log({"messaging" , "server"},"Got request: " + request + " , response: " + response);
			return response;
		}
	}
	Logger::GetLogger()->Log({"messaging" , "server"},"Got request: " + request + " , response: " + response);
	return response;
}

void LineSharingServer::AddCapability(StringCapability* capability) {

	capability->setOwner(this);
	m_capabilities.push_back(capability);

}

LineSharingServer::LineSharingServer(const LineSharingServer& old_obj):
m_port(old_obj.m_port),
m_startPort(old_obj.m_startPort),
m_endPort(old_obj.m_endPort),
m_clientConnectionIdCounter(old_obj.m_clientConnectionIdCounter),
m_stopServer(old_obj.m_stopServer),
m_serverStarted(old_obj.m_serverStarted)
{

	m_capabilities.clear();
	AddCapability(new SendAvailableLineCapability());
	AddCapability(new SendAvailableLineNumberCapability());

}

void LineSharingServer::WaitForConnectionsToClose() {

	void *status;

	for(pthread_t* connectionHandler: m_connectionThreads)
	{
		int pthreadResult = pthread_join(*connectionHandler, &status);
		if (pthreadResult) {
			Logger::GetLogger()->Log({"error"},"Error: client thread unable to join,");
		}
	}

	pthread_attr_destroy(&m_serverAttr);

}

pthread_t *LineSharingServer::getServerThread(){
	return &serverThread;
}

void LineSharingServer::setServerThread(pthread_t serverThread) {
	this->serverThread = serverThread;
}

bool LineSharingServer::NextPort() {

	m_port++;

	if(m_port > m_endPort)
	{
		return false;
	}
	else
	{
		return true;
	}
}

LineCollection* LineSharingServer::getLineCollection() {
	return m_lineCollection;
}

void LineSharingServer::setLineCollection(LineCollection* lineCollection) {
	m_lineCollection = lineCollection;
}

void LineSharingServer::SendDiscoveredClientData(string clientIp, bool isCompatible) {

	if(m_discoveredClientDataSend)
	{
		return;
	}
	DiscoveredApplications::AddDiscoveredApp(clientIp,m_port,"Client",isCompatible);
	m_discoveredClientDataSend = true;

}
