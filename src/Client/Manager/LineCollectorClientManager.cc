/*
 * LineCollectorClientManager.cc
 *
 *  Created on: Dec 22, 2018
 *      Author: temp
 */

#include <pthread.h>
#include <unistd.h>

#include "LineCollectorClientManager.h"
#include "../../Log/Logger.h"

LineCollectorClientManager::LineCollectorClientManager(ThreadConfig config,
		NetworkConfig netConfig):
m_config(config),
m_netConfig(netConfig),
m_threadsStarted(false)
{

}

void LineCollectorClientManager::StartThreads() {

	if(m_threadsStarted)
	{
		StopThreads();
	}

	m_threadsStarted = true;

	LineCollectorClient client(m_netConfig);
	m_clients.insert(m_clients.begin(),m_config.getNumOfClients(),client);

	for(LineCollectorClient client : m_clients)
	{
		int pthreadResult;

		pthread_attr_init(&m_attr);
		pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);

		pthreadResult = pthread_create(client.getClientThreadId(), NULL, &LineCollectorClient::StartClientLoopPthreadFacade, (void*)&client);
		if(pthreadResult)
		{
			Logger::GetLogger()->Log({"error"},"Error: failed to create server thread");
		}
	}

}

void LineCollectorClientManager::StopThreads() {

	void *status;
	pthread_attr_destroy(&m_attr);

	if(!m_threadsStarted)
	{
		return;
	}

	m_threadsStarted = false;

	for(LineCollectorClient client : m_clients)
	{
		int pthreadResult = pthread_join(*(client.getClientThreadId()), &status);
		if (pthreadResult) {
			Logger::GetLogger()->Log({"error"},"Error: server thread unable to join,");
		}
	}

	m_clients.clear();

}



