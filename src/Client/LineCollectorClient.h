/*
 * LineCollectorClient.h
 *
 *  Created on: Dec 17, 2018
 *      Author: temp
 */

#ifndef CLIENT_LINECOLLECTORCLIENT_H_
#define CLIENT_LINECOLLECTORCLIENT_H_

#include <string>

#include "Requests/Request.h"

using namespace std;

#define WAITING_TIME_BETWEEN_CONNECTIONS 1
#define WAIT_FOR_REQUEST_RESPONSE_MAX 3
#define WAIT_FOR_REQUEST_RESPONSE_INTERVAL 1

class LineCollectorClient
// scans certain IP range, on certain port range, when there is server and has line we don't have yet
// (check with LineCollection) then collects it and sends to LineCollection.
{
public:

	LineCollectorClient(string startIP, string endIP, int startPort, int endPort);

	void* StartClientLoop();

	static void* StartClientPthreadFacade(void *LineCollectorClientPointer);

private:

	void NextIpAndPort();
	void StartClientOnSelectedIpAndPort();
	bool EstablishConnection();
	void SendRequest();
	void WaitForRequestResponse();
	void HandleRequestResponse();
	void CloseConnection();

	string m_startIP,m_endIP;
	int m_startPort,m_endPort;
	string m_selectedIP;
	int m_selectedPort;

	int m_sockedId;
	bool m_stopConnection;
	bool m_stopConnectionLoop;

	Request *m_activeRequest;
	string m_receivedResponse;
};

#endif /* CLIENT_LINECOLLECTORCLIENT_H_ */
