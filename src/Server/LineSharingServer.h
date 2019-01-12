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
#include "../CollectedData/Lines/LineCollection.h"

#define TIME_WITHOUT_REQUESTS_TO_CLOSE_SOCKET_CONNECTION 4
#define WAIT_FOR_REQUEST_INTERVAL 1

class LineSharingServer
// when is started, waits on certain port and answers requests, with data from owned line
{
public:

	LineSharingServer(int startPort,int endPort);
	LineSharingServer (const LineSharingServer &old_obj);
	~LineSharingServer();

	void* StartServer();
	static void* StartServerPthreadFacade(void *LineSharingServerPointer);

	void StopServer();
	pthread_t *getServerThread();
	void setServerThread(pthread_t serverThread);
	LineCollection* getLineCollection();
	void setLineCollection(LineCollection* lineCollection);

	void AddCapability(StringCapability* capability);

	void SendDiscoveredClientData(string clientIp, bool isCompatible);

private:

	bool NextPort();
	void* Connection(int newsockfd);
	static void* ConnectionPthreadFacade(void *LineSharingServerPointer);

	string CreateResponseForClientRequest(string request);

    void WaitForConnectionsToClose();

    int m_startPort,m_endPort;
	int m_port;
	vector<StringCapability*> m_capabilities;
	int m_clientConnectionIdCounter;
	bool m_discoveredClientDataSend;
	bool m_stopServer;
	bool m_serverStarted;
    vector<pthread_t*> m_connectionThreads;
    pthread_attr_t m_serverAttr;

    pthread_t serverThread;

    LineCollection *m_lineCollection;
    map<int,string> m_connectedClientsIPs;
};

#endif /* LINESHARINGSERVER_H_ */
