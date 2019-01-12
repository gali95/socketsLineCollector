/*
 * LineCollectorClient.cpp
 *
 *  Created on: Dec 17, 2018
 *      Author: temp
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

#ifdef __linux__

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#elif _WIN32

#include "../Stubs/LinuxSockets.h"

#endif

#include "LineCollectorClient.h"
#include "Requests/BasicRequestsImpl/AvailableLineNumberRequest.h"
#include "../Log/Logger.h"
#include "../CollectedData/DiscoveredApplicationsInfo/DiscoveredApplications.h"

LineCollectorClient::LineCollectorClient(string startIP, string endIP, int startPort, int endPort):
m_startIP(startIP),
m_endIP(endIP),
m_startPort(startPort),
m_endPort(endPort),
m_selectedIP(startIP),
m_selectedPort(startPort),
m_activeRequest(0)
{
	Request *startingRequest = new AvailableLineNumberRequest();
	setActiveRequest(startingRequest);
}

void LineCollectorClient::StartClientOnSelectedIpAndPort()
{

	if(EstablishConnection())
	{
		m_stopConnection = false;
		while(!m_stopConnection)
		{
			SendRequest();
			WaitForRequestResponse();
			HandleRequestResponse();
		}
		CloseConnection();
	}
}

void* LineCollectorClient::StartClientLoop() {

	m_stopConnectionLoop = false;
	while(!m_stopConnectionLoop)
	{
		StartClientOnSelectedIpAndPort();
		NextIpAndPort();
		sleep(WAITING_TIME_BETWEEN_CONNECTIONS);
	}
	pthread_exit(NULL);
}

void* LineCollectorClient::StartClientLoopPthreadFacade(
		void* LineCollectorClientPointer) {

	return ((LineCollectorClient*)LineCollectorClientPointer)->StartClientLoop();

}

void LineCollectorClient::NextIpAndPort() {

	m_selectedPort++;

	if(m_selectedPort > m_endPort)
	{
		m_selectedPort = m_startPort;

		struct in_addr nextIpAdress,maxIpAdress,minIpAdress;
		inet_aton(m_selectedIP.c_str(), &nextIpAdress);
		inet_aton(m_endIP.c_str(), &maxIpAdress);
		inet_aton(m_startIP.c_str(), &minIpAdress);

		int diff = ntohl(maxIpAdress.s_addr) - ntohl(minIpAdress.s_addr);

		nextIpAdress.s_addr = htonl(ntohl(nextIpAdress.s_addr) + 1);

		if(nextIpAdress.s_addr > maxIpAdress.s_addr)
		{
			m_selectedIP = m_startIP;
		}
		else
		{
			m_selectedIP = inet_ntoa(nextIpAdress);
		}
	}

}

bool LineCollectorClient::EstablishConnection() {

	struct sockaddr_in serv_addr;
	struct hostent *server;

	m_sockedId = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockedId < 0)
	{
		Logger::GetLogger()->Log({"error","client"},"ERROR opening socket");
		return false;
	}
	server = gethostbyname(m_selectedIP.c_str());
	if (server == NULL) {
		Logger::GetLogger()->Log({"error","client"},"ERROR, no such host");
		return false;
	}
	bzero((char *) &serv_addr, 0);
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(m_selectedPort);
	if (connect(m_sockedId,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		Logger::GetLogger()->Log({"error","client"},"ERROR connecting");
		return false;
	}
	else
	{
		m_discoveredServerDataSend = false;
		return true;
	}

}

void LineCollectorClient::SendRequest() {

	int n;

	string requestString = m_activeRequest->GetRequest();
	n = write(m_sockedId,requestString.c_str(),strlen(requestString.c_str()));
	if (n < 0)
	{
		Logger::GetLogger()->Log({"error","client"},"ERROR writing to socket");
	}
	else
	{
		Logger::GetLogger()->Log({"client","socket_write"},requestString +
				" port:" + to_string(m_selectedPort) +
				" wyslane bajty: " + to_string(n));
	}
}

void LineCollectorClient::WaitForRequestResponse() {

	char buffer[256];
	double timeToCloseConnection = WAIT_FOR_REQUEST_RESPONSE_MAX;
	int n;

	while(timeToCloseConnection > 0)
	{
		bzero(buffer,256);
		n = read(m_sockedId,buffer,255);
		if (n < 0)
		{
			Logger::GetLogger()->Log({"error"},"ERROR reading from socket");
			timeToCloseConnection -= WAIT_FOR_REQUEST_RESPONSE_INTERVAL;
			sleep(WAIT_FOR_REQUEST_RESPONSE_INTERVAL);
		}
		else if (n > 0)
		{
			m_receivedResponse = buffer;
			Logger::GetLogger()->Log({"client","socket_read"},(string)buffer +
					" port:" + to_string(m_selectedPort) +
					" odebrane bajty: " + to_string(n));
			break;
		}
	}

	if(timeToCloseConnection <= 0)
	{
		LogDiscoveredServerData(false);
		CloseConnection();
	}

}

void LineCollectorClient::HandleRequestResponse() {

	Logger::GetLogger()->Log({"received" , "client"},"Got response from server: " + m_receivedResponse);
	m_activeRequest->HandleReply(m_receivedResponse);

}

LineCollectorClient::LineCollectorClient(NetworkConfig netConfig):
m_startIP(netConfig.getStartIp()),
m_endIP(netConfig.getEndIp()),
m_startPort(netConfig.getStartPort()),
m_endPort(netConfig.getEndPort()),
m_selectedIP(netConfig.getStartIp()),
m_selectedPort(netConfig.getStartPort()),
m_activeRequest(0)
{

	Request *startingRequest = new AvailableLineNumberRequest();
	setActiveRequest(startingRequest);

}

LineCollectorClient::LineCollectorClient(const LineCollectorClient& old_obj):
m_startIP(old_obj.m_startIP),
m_endIP(old_obj.m_endIP),
m_startPort(old_obj.m_startPort),
m_endPort(old_obj.m_endPort),
m_selectedIP(old_obj.m_selectedIP),
m_selectedPort(old_obj.m_selectedPort),
m_activeRequest(old_obj.m_activeRequest)
{

	Request *startingRequest = new AvailableLineNumberRequest();
	setActiveRequest(startingRequest);

}

void LineCollectorClient::CloseConnection() {

	close(m_sockedId);

}

pthread_t* LineCollectorClient::getClientThreadId(){
	return &clientThread;
}

void LineCollectorClient::setClientThreadId(pthread_t clientThreadId) {
	clientThread = clientThreadId;
}

Request*& LineCollectorClient::getActiveRequest() {
	return m_activeRequest;
}

void LineCollectorClient::setActiveRequest(Request*& activeRequest) {
	if(!m_activeRequest)
	{
		delete m_activeRequest;
	}
	m_activeRequest = activeRequest;
	m_activeRequest->setOwner(this);
}

LineCollection*& LineCollectorClient::getLineCollection() {
	return m_lineCollection;
}

void LineCollectorClient::setLineCollection(
		LineCollection*& lineCollection) {
	m_lineCollection = lineCollection;
}

void LineCollectorClient::StopCurrentConnection()
{
	m_stopConnection = true;
}

void LineCollectorClient::LogDiscoveredServerData(bool isCompatible) {

	if(m_discoveredServerDataSend)
	{
		return;
	}
	DiscoveredApplications::AddDiscoveredApp(m_selectedIP,m_selectedPort,"Server",isCompatible);
	m_discoveredServerDataSend = true;

}
