/*
 * LineCollectorClientManager.h
 *
 *  Created on: Dec 22, 2018
 *      Author: temp
 */

#ifndef CLIENT_MANAGER_LINECOLLECTORCLIENTMANAGER_H_
#define CLIENT_MANAGER_LINECOLLECTORCLIENTMANAGER_H_

#include <vector>

#include "../../Config/NetworkConfig.h"
#include "../../Config/ThreadConfig.h"
#include "../LineCollectorClient.h"

class LineCollectorClientManager
{
public:
	LineCollectorClientManager(ThreadConfig config, NetworkConfig netConfig, LineCollection *collectionPtr);

	void StartThreads();
	void StopThreads();

	void SetLineCollection(LineCollection *collectionPtr);
private:

	void prepareClients();
	int CountDifferenceBetweenIPs(string startIP, string endIP);
	string IncreaseIP(string ip, int ipIncrease);

	vector<LineCollectorClient> m_clients;
	ThreadConfig m_config;
	NetworkConfig m_netConfig;
	bool m_threadsStarted;
	pthread_attr_t m_attr;
	LineCollection *m_collectionPtr;

};

#endif /* CLIENT_MANAGER_LINECOLLECTORCLIENTMANAGER_H_ */
