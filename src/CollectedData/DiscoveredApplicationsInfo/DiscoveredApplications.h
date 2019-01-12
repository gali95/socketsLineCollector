/*
 * DiscoveredApplications.h
 *
 *  Created on: Jan 6, 2019
 *      Author: temp
 */

#ifndef COLLECTEDDATA_DISCOVEREDAPPLICATIONSINFO_DISCOVEREDAPPLICATIONS_H_
#define COLLECTEDDATA_DISCOVEREDAPPLICATIONSINFO_DISCOVEREDAPPLICATIONS_H_

#include <string>
#include <vector>
#include <map>

#include "DiscoveredApplicationStruct.h"

using namespace std;

class DiscoveredApplications
{
public:
	static void AddDiscoveredApp(string ip, int port, string serverOrClient, bool isCompatible);
	static map<pair<string,int>,DiscoveredApplicationStruct> &GetDataMap();
private:
	static map<pair<string,int>,DiscoveredApplicationStruct> m_discoveredApplications;
};

#endif /* COLLECTEDDATA_DISCOVEREDAPPLICATIONSINFO_DISCOVEREDAPPLICATIONS_H_ */
