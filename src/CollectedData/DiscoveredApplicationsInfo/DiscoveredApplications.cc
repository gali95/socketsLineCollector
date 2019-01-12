/*
 * DiscoveredApplications.cc
 *
 *  Created on: Jan 6, 2019
 *      Author: temp
 */

#include "DiscoveredApplications.h"

map<pair<string,int>,DiscoveredApplicationStruct> DiscoveredApplications::m_discoveredApplications = { };


void DiscoveredApplications::AddDiscoveredApp(string ip, int port,
		string serverOrClient, bool isCompatible) {

	if(m_discoveredApplications.find(make_pair(ip,port)) == m_discoveredApplications.end())
	{
		DiscoveredApplicationStruct infoStruct;
		infoStruct.serverOrClient = serverOrClient;
		infoStruct.compatibleWithOurApp = isCompatible;
		m_discoveredApplications[make_pair(ip,port)] = infoStruct;
	}

}

map<pair<string,int>,DiscoveredApplicationStruct> &DiscoveredApplications::GetDataMap() {

	return m_discoveredApplications;

	/*
	vector<string> stringsToReturn;
	for(map<pair<string,int>,DiscoveredApplicationStruct>::iterator it = m_discoveredApplications.begin() ; it != m_discoveredApplications.end(); ++it)
	{
		string partString = "[" + (*it).first.first + ":" + to_string((*it).first.second) + "]\t" + (*it).second.serverOrClient + "\t" + to_string((*it).second.compatibleWithOurApp);
		stringsToReturn.push_back(partString);
	}
	return stringsToReturn;
	*/
}
