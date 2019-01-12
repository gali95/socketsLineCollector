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
		NetworkConfig netConfig,
		LineCollection *collectionPtr):
m_config(config),
m_netConfig(netConfig),
m_threadsStarted(false),
m_collectionPtr(collectionPtr)
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

	LineSharingServer serverToInsert(m_netConfig.getStartPort(), m_netConfig.getEndPort());
	if(m_config.getNumOfServers() > 0)
	{
		m_servers.insert(m_servers.begin(),m_config.getNumOfServers(),serverToInsert);
	}

	for(std::vector<LineSharingServer>::iterator serverIt = m_servers.begin() ; serverIt != m_servers.end(); ++serverIt)
	{
		serverIt->setLineCollection(m_collectionPtr);

		int pthreadResult;

		pthread_attr_init(&m_attr);
		pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);

		pthreadResult = pthread_create(serverIt->getServerThread(), NULL, &LineSharingServer::StartServerPthreadFacade, (void*)serverIt.base());
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

void LineSharingServerManager::SetLineCollection(
		LineCollection* collectionPtr) {

	m_collectionPtr = collectionPtr;

}

bool LineSharingServerManager::AreConfigsOK() {

	return true;    // refactor maybe?

}
