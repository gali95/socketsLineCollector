/*
 * ConfigBuilder.cc
 *
 *  Created on: Dec 24, 2018
 *      Author: temp
 */

#include "ConfigBuilder.h"

LineCollectorConfigCollection ConfigBuilder::GetDefaultConfig() {

	LineCollectorConfigCollection config;
	config.m_lineToShareConfig = GetDefaultLineToShareConfig();
	config.m_networkConfig = GetDefaultNetworkConfig();
	config.m_threadConfig = GetDefaultThreadConfig();

	return config;
}

vector<LineCollectorConfigCollection> ConfigBuilder::GetLocalHostTestingConfigs(
		int numOfLineCollectors) {

	vector<LineCollectorConfigCollection> configsToReturn;
	vector<NetworkConfig> networkConfigs = GetLocalHostTestingNetworkConfigs(numOfLineCollectors);
	int lineNumber = 1;

	for(NetworkConfig networkConfig : networkConfigs)
	{
		LineCollectorConfigCollection config;
		config.m_lineToShareConfig = GetDefaultLineToShareConfig(lineNumber++);
		config.m_networkConfig = networkConfig;
		config.m_threadConfig = GetDefaultThreadConfig();
		configsToReturn.push_back(config);
	}

	return configsToReturn;
}

ThreadConfig ConfigBuilder::GetDefaultThreadConfig() {

	ThreadConfig config;
	config.setNumOfClients(4);
	config.setNumOfServers(4);

	return config;
}

LineToShareConfig ConfigBuilder::GetDefaultLineToShareConfig() {

	return GetDefaultLineToShareConfig(1);
}

NetworkConfig ConfigBuilder::GetDefaultNetworkConfig() {

	NetworkConfig config;
	config.setStartIp("192.168.1.0");
	config.setEndIp("192.168.1.255");
	config.setStartPort(9000);
	config.setEndPort(9200);

	return config;
}

LineToShareConfig ConfigBuilder::GetDefaultLineToShareConfig(int lineNumber) {

	LineToShareConfig config;
	config.setLineNumber(lineNumber);

	switch(lineNumber)
	{
	case 1:
		config.setLine("Litwo, ojczyzno moja,");
		break;
	case 2:
		config.setLine("ty jestes jak zdrowie!");
		break;
	default:
		config.setLine("There was no line with such number.");  // add description which line
		break;
	}

	return config;

}

vector<NetworkConfig> ConfigBuilder::GetLocalHostTestingNetworkConfigs(
		int numOfLineCollectors) {

	vector<NetworkConfig> configs;

	NetworkConfig config;
	config.setStartIp("127.0.0.1");
	config.setEndIp("127.0.0.1");
	config.setStartPort(9000);
	config.setEndPort(9200);

	configs.insert(configs.begin(),numOfLineCollectors,config);

	return configs;
}
