/*
 * LineCollectorClientManager.h
 *
 *  Created on: Dec 22, 2018
 *      Author: temp
 */

#ifndef SERVER_MANAGER_LINESHARINGSERVERMANAGER_H_
#define SERVER_MANAGER_LINESHARINGSERVERMANAGER_H_

#include <vector>

#include "../../Config/NetworkConfig.h"
#include "../../Config/ThreadConfig.h"
#include "../LineSharingServer.h"

class LineSharingServerManager
{
public:
	LineSharingServerManager(ThreadConfig config, NetworkConfig netConfig);

	void StartThreads();
	void StopThreads();

private:

	bool AreConfigsOK();

	vector<LineSharingServer> m_servers;
	ThreadConfig m_config;
	NetworkConfig m_netConfig;
	bool m_threadsStarted;
	pthread_attr_t m_attr;

};

#endif /* SERVER_MANAGER_LINESHARINGSERVERMANAGER_H_ */
