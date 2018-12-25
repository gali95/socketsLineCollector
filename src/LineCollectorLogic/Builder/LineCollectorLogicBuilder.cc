/*
 * LineCollectorLogicBuilder.cc
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#include "LineCollectorLogicBuilder.h"
#include "../../Config/Builder/ConfigBuilder.h"

LineCollectorLogic LineCollectorLogicBuilder::BuildDefault() {

	LineCollectorLogic logic(ConfigBuilder::GetDefaultConfig());
	return logic;

}

vector<LineCollectorLogic> LineCollectorLogicBuilder::BuildForLocalHost(int numOfCollectors) {

	vector<LineCollectorConfigCollection> configs = ConfigBuilder::GetLocalHostTestingConfigs(numOfCollectors);
	vector<LineCollectorLogic> logics;
	LineCollectorLogic *newCreatedLogic;

	for(LineCollectorConfigCollection config: configs)
	{
		newCreatedLogic = new LineCollectorLogic(config);
		logics.push_back(*newCreatedLogic);
		delete newCreatedLogic;
	}

	return logics;
}
