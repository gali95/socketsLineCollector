/*
 * LineCollectorClientManager.cc
 *
 *  Created on: Dec 22, 2018
 *      Author: temp
 */

#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "LineCollectorClientManager.h"
#include "../../Log/Logger.h"

LineCollectorClientManager::LineCollectorClientManager(ThreadConfig config,
		NetworkConfig netConfig,
		LineCollection *collectionPtr):
m_config(config),
m_netConfig(netConfig),
m_threadsStarted(false),
m_collectionPtr(collectionPtr)
{

}

void LineCollectorClientManager::StartThreads() {

	if(m_threadsStarted)
	{
		StopThreads();
	}

	m_threadsStarted = true;

	prepareClients();

	for(std::vector<LineCollectorClient>::iterator clientIt = m_clients.begin() ; clientIt != m_clients.end(); ++clientIt)
	{
		clientIt->setLineCollection(m_collectionPtr);

		int pthreadResult;

		pthread_attr_init(&m_attr);
		pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);

		pthreadResult = pthread_create(clientIt->getClientThreadId(), NULL, &LineCollectorClient::StartClientLoopPthreadFacade, (void*)clientIt.base());
		if(pthreadResult)
		{
			Logger::GetLogger()->Log({"error"},"Error: failed to create client thread");
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

int LineCollectorClientManager::CountDifferenceBetweenIPs(string startIP,
		string endIP) {

	struct in_addr maxIpAdress,minIpAdress;

	inet_aton(endIP.c_str(), &maxIpAdress);
	inet_aton(startIP.c_str(), &minIpAdress);

	int diff = ntohl(maxIpAdress.s_addr) - ntohl(minIpAdress.s_addr) + 1;

	return diff;
}

void LineCollectorClientManager::prepareClients() {

	if(m_config.getNumOfClients() < 1)
	{
		return;
	}

	LineCollectorClient *initClient;
	NetworkConfig dividedIpRangeNetworkConfig = m_netConfig;

	int i;
	int ipsInRange = CountDifferenceBetweenIPs(m_netConfig.getStartIp(),m_netConfig.getEndIp());

	m_clients.clear();

	for(i=0; i < m_config.getNumOfClients() - 1; i++)
	{
		dividedIpRangeNetworkConfig.setStartIp(IncreaseIP(m_netConfig.getStartIp(),((double)ipsInRange/m_config.getNumOfClients()*i)));
		dividedIpRangeNetworkConfig.setEndIp(IncreaseIP(m_netConfig.getStartIp(),((double)ipsInRange/m_config.getNumOfClients()*(i+1)-1)));
		initClient = new LineCollectorClient(dividedIpRangeNetworkConfig);
		m_clients.push_back(*initClient);
		delete initClient;
	}

	dividedIpRangeNetworkConfig.setStartIp(IncreaseIP(m_netConfig.getStartIp(),((double)ipsInRange/m_config.getNumOfClients()*i)));
	dividedIpRangeNetworkConfig.setEndIp(m_netConfig.getEndIp());
	initClient = new LineCollectorClient(dividedIpRangeNetworkConfig);
	m_clients.push_back(*initClient);
	delete initClient;

}

void LineCollectorClientManager::SetLineCollection(
		LineCollection* collectionPtr) {

	m_collectionPtr = collectionPtr;

}

string LineCollectorClientManager::IncreaseIP(string ip, int ipIncrease) {

	struct in_addr nextIpAdress;
	inet_aton(ip.c_str(), &nextIpAdress);

	nextIpAdress.s_addr = htonl(ntohl(nextIpAdress.s_addr) + ipIncrease);

	char* nextIpAdressChar = inet_ntoa(nextIpAdress);
	string nextIpAdressString(nextIpAdressChar);

	return nextIpAdressString;

}
