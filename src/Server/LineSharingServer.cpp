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

#elif _WIN32

#include "../Stubs/LinuxSockets.h"

#endif

#include <pthread.h>

#include "LineSharingServer.h"
#include "../Log/Logger.h"
#include "ConnectionArguments.h"

LineSharingServer::LineSharingServer(int port, vector<StringCapability*> capabilities):
m_port(port),
m_clientConnectionIdCounter(1),
m_capabilities(capabilities),
m_stopServer(false),
m_serverStarted(false)
{

}

void* LineSharingServer::StartServer()
{

	if(m_serverStarted || m_stopServer)
	{
		pthread_exit(NULL);
	}

	m_serverStarted = true;

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
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
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while(!m_stopServer)
    {
        newsockfd = accept(sockfd,
                    (struct sockaddr *) &cli_addr,
                    &clilen);
        if (newsockfd >= 0)
        {
        	m_connectionThreads.push_back(new pthread_t());

        	ConnectionArguments *connArgs = new ConnectionArguments(this, m_clientConnectionIdCounter++);

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

    WaitForConnectionsToClose();

    close(sockfd);
    Logger::GetLogger()->Log({"info"},"LineSharingServer::startServer() finished");
    pthread_exit(NULL);
}

void* LineSharingServer::Connection(int newsockfd) {

	char buffer[256];
	double timeToCloseConnection = TIME_WITHOUT_REQUESTS_TO_CLOSE_SOCKET_CONNECTION;
	int n;

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
		else
		{
			string requestResponse = CreateResponseForClientRequest(buffer);
			if(requestResponse != "")
			{
				bzero(buffer,256);
				n = write(newsockfd,reinterpret_cast<void*>(&requestResponse),requestResponse.length());
				if (n < 0)
				{
					Logger::GetLogger()->Log({"error"},"ERROR writing to socket");
				}
				timeToCloseConnection = TIME_WITHOUT_REQUESTS_TO_CLOSE_SOCKET_CONNECTION;
			}

		}
		if(m_stopServer)
		{
			break;
		}
	}
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

	for(StringCapability *cap: m_capabilities)
	{
		if(cap->CanHandleString(request))
		{
			response = cap->HandleString(request);
			return response;
		}
	}
	return response;
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
