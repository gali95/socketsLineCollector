/*
 * ConfigBuilder.h
 *
 *  Created on: Dec 24, 2018
 *      Author: temp
 */

#ifndef CONFIG_BUILDER_CONFIGBUILDER_H_
#define CONFIG_BUILDER_CONFIGBUILDER_H_

#include <vector>

#include "../LineCollectorConfigCollection.h"

class ConfigBuilder
{
public:

	static LineCollectorConfigCollection GetDefaultConfig();

	static vector<LineCollectorConfigCollection> GetLocalHostTestingConfigs(int numOfLineCollectors);

private:

	static ThreadConfig GetDefaultThreadConfig();
	static LineToShareConfig GetDefaultLineToShareConfig();
	static LineToShareConfig GetDefaultLineToShareConfig(int lineNumber);
	static NetworkConfig GetDefaultNetworkConfig();
	static vector<NetworkConfig> GetLocalHostTestingNetworkConfigs(int numOfLineCollectors);

};

#endif /* CONFIG_BUILDER_CONFIGBUILDER_H_ */
