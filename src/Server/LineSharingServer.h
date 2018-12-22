/*
 * LineSharingServer.h
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */

#ifndef LINESHARINGSERVER_H_
#define LINESHARINGSERVER_H_

#include <vector>

#include "Capabilities/StringCapability.h"

#define TIME_WITHOUT_REQUESTS_TO_CLOSE_SOCKET_CONNECTION 4
#define WAIT_FOR_REQUEST_INTERVAL 1

class LineSharingServer
// when is started, waits on certain port and answers requests, with data from owned line
{
public:

	LineSharingServer(int port, vector<StringCapability*> capabilities);

	void* StartServer();
	static void* StartServerPthreadFacade(void *LineSharingServerPointer);

	void StopServer();

private:

	void* Connection(int newsockfd);
	static void* ConnectionPthreadFacade(void *LineSharingServerPointer);

	string CreateResponseForClientRequest(string request);

    void WaitForConnectionsToClose();

	int m_port;
	vector<StringCapability*> m_capabilities;
	int m_clientConnectionIdCounter;
	bool m_stopServer;
	bool m_serverStarted;
    vector<pthread_t*> m_connectionThreads;
    pthread_attr_t m_serverAttr;
};

#endif /* LINESHARINGSERVER_H_ */
