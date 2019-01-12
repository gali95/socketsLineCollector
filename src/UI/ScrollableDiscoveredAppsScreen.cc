/*
 * ScrollableDiscoveredAppsScreen.cc
 *
 *  Created on: Jan 12, 2019
 *      Author: temp
 */

#include "ScrollableDiscoveredAppsScreen.h"
#include "../CollectedData/DiscoveredApplicationsInfo/DiscoveredApplications.h"

bool ScrollableDiscoveredAppsScreen::PointToFirstMessage() {

	map<pair<string,int>,DiscoveredApplicationStruct> &lines = DiscoveredApplications::GetDataMap();

	if(lines.empty())
	{
		return false;
	}
	else
	{
		m_messagePointer = lines.begin();
		return true;
	}

}

bool ScrollableDiscoveredAppsScreen::PointToNextMessage() {

	map<pair<string,int>,DiscoveredApplicationStruct> &lines = DiscoveredApplications::GetDataMap();

	m_messagePointer++;
	if(m_messagePointer == lines.end())
	{
		return false;
	}
	else
	{
		return true;
	}

}

string ScrollableDiscoveredAppsScreen::GetMessage() {

	return "[" + (*m_messagePointer).first.first + ":" + to_string((*m_messagePointer).first.second) + "]\t" + (*m_messagePointer).second.serverOrClient + "\t" + to_string((*m_messagePointer).second.compatibleWithOurApp);

}
