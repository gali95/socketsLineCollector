//============================================================================
// Name        : exampl3.cpp
// Author      : gali
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include "Server/LineSharingServer.h"
#include "Client/LineCollectorClient.h"
#include "LineCollectorLogic/LineCollectorLogic.h"
#include "LineCollectorLogic/Builder/LineCollectorLogicBuilder.h"
#include "Log/Logger.h"

using namespace std;

int main() {



	LineCollectorLogic logic = LineCollectorLogicBuilder::BuildDefault();

	/*

	LineSharingServer server(9990,9999);
	LineCollectorClient client("127.0.0.1","endIpRangePlaceholder",9991,9990);

	pthread_t serverThread,clientThread;
	pthread_attr_t attr;
	void *status;
	int pthreadResult;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/////////////// starting threads

	pthreadResult = pthread_create(&serverThread, NULL, &LineSharingServer::StartServerPthreadFacade, &server);
	if(pthreadResult)
	{
		Logger::GetLogger()->Log({"error"},"Error: failed to create server thread");
	}

	sleep(7);

	pthreadResult = pthread_create(&clientThread, NULL, &LineCollectorClient::StartClientLoopPthreadFacade, &client);
	if(pthreadResult)
	{
		Logger::GetLogger()->Log({"error"},"Error: failed to create client thread");
	}

	////////////////// waiting for threads to end

	pthread_attr_destroy(&attr);

	pthreadResult = pthread_join(serverThread, &status);
	if (pthreadResult) {
		Logger::GetLogger()->Log({"error"},"Error: server thread unable to join,");
	}

	pthreadResult = pthread_join(clientThread, &status);
	if (pthreadResult) {
		Logger::GetLogger()->Log({"error"},"Error: client thread unable to join,");
	}

	pthread_exit(NULL);

	*/
}
