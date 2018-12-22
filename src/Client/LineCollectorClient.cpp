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
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "LineCollectorClient.h"
#include "../Log/Logger.h"

LineCollectorClient::LineCollectorClient(string startIP, string endIP, int startPort, int endPort):
m_startIP(startIP),
m_endIP(endIP),
m_startPort(startPort),
m_endPort(endPort),
m_selectedIP(startIP),
m_selectedPort(startPort)
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

void* LineCollectorClient::StartClientPthreadFacade(
		void* LineCollectorClientPointer) {

	return ((LineCollectorClient *)LineCollectorClientPointer)->StartClientLoop();

}

void LineCollectorClient::NextIpAndPort() {



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
	bzero((char *) &serv_addr, sizeof(serv_addr));
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

void LineCollectorClient::CloseConnection() {

	close(m_sockedId);

}
