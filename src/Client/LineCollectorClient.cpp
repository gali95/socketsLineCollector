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
#include "../Log/Logger.h"

LineCollectorClient::LineCollectorClient(string startIP, string endIP, int startPort, int endPort):
m_startIP(startIP),
m_endIP(endIP),
m_startPort(startPort),
m_endPort(endPort),
m_selectedIP(startIP),
m_selectedPort(startPort)//,
//clientThreadID(new pthread_t())
{

}

void LineCollectorClient::StartClientOnSelectedIpAndPort()
{

	if(EstablishConnection())
	{
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

	return ((LineCollectorClient *)LineCollectorClientPointer)->StartClientLoop();

}

void LineCollectorClient::NextIpAndPort() {

	m_selectedPort++;

	if(m_selectedPort > m_endPort)
	{
		m_selectedPort = m_startPort;

		struct in_addr *nextIpAdress,*maxIpAdress;
		inet_aton(m_selectedIP.c_str(), nextIpAdress);
		inet_aton(m_endIP.c_str(), maxIpAdress);

		nextIpAdress->s_addr++;

		if(nextIpAdress > maxIpAdress)
		{
			m_selectedIP = m_startIP;
		}
		else
		{
			m_selectedIP = inet_ntoa(*nextIpAdress);
		}
	}

}

bool LineCollectorClient::EstablishConnection() {

	int n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	m_sockedId = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockedId < 0)
	{
		Logger::GetLogger()->Log({"error","client"},"ERROR opening socket");
	}
	server = gethostbyname(m_selectedIP.c_str());
	if (server == NULL) {
		Logger::GetLogger()->Log({"error","client"},"ERROR, no such host");
		exit(0);
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
		else
		{
			m_receivedResponse = buffer;
			break;
		}
	}

}

void LineCollectorClient::HandleRequestResponse() {

	m_activeRequest->HandleReply(m_receivedResponse);

}

LineCollectorClient::LineCollectorClient(NetworkConfig netConfig):
m_startIP(netConfig.getStartIp()),
m_endIP(netConfig.getEndIp()),
m_startPort(netConfig.getStartPort()),
m_endPort(netConfig.getEndPort()),
m_selectedIP(netConfig.getStartIp()),
m_selectedPort(netConfig.getStartPort())
{



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
