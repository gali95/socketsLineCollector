/*
 * LineCollectorClientManager.cc
 *
 *  Created on: Dec 22, 2018
 *      Author: temp
 */

#include <pthread.h>
#include <unistd.h>

#include "LineSharingServerManager.h"
#include "../../Log/Logger.h"

LineSharingServerManager::LineSharingServerManager(ThreadConfig config,
		NetworkConfig netConfig):
m_config(config),
m_netConfig(netConfig),
m_threadsStarted(false)
{

}

void LineSharingServerManager::StartThreads() {

	if(!AreConfigsOK())
	{
		return;
	}
	if(m_threadsStarted)
	{
		StopThreads();
	}

	m_threadsStarted = true;

	LineSharingServer server(m_netConfig.getStartPort(), m_netConfig.getEndPort());
	m_servers.insert(m_servers.begin(),m_config.getNumOfClients(),server);

	for(LineSharingServer client : m_servers)
	{
		int pthreadResult;

		pthread_attr_init(&m_attr);
		pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);

		pthreadResult = pthread_create(server.getServerThread(), NULL, &LineSharingServer::StartServerPthreadFacade, (void*)&server);
		if(pthreadResult)
		{
			Logger::GetLogger()->Log({"error"},"Error: failed to create server thread");
		}
	}

}

void LineSharingServerManager::StopThreads() {

	void *status;
	pthread_attr_destroy(&m_attr);

	if(!m_threadsStarted)
	{
		return;
	}

	m_threadsStarted = false;

	for(LineSharingServer server : m_servers)
	{
		int pthreadResult = pthread_join(*(server.getServerThread()), &status);
		if (pthreadResult) {
			Logger::GetLogger()->Log({"error"},"Error: server thread unable to join,");
		}
	}

	m_servers.clear();

}

bool LineSharingServerManager::AreConfigsOK() {

	return true;    // refactor maybe?

}



