/*
 * PrintableLogs.cc
 *
 *  Created on: Jan 8, 2019
 *      Author: temp
 */

#include "PrintableLogs.h"

PrintableLogs::PrintableLogs():
m_lastCheckedMainLogId(0),
m_nextLogId(0)
{

}

void PrintableLogs::SetFilters(vector<string> filters) {

	m_filters = filters;
	ClearLogs();

}

vector<string> PrintableLogs::GetFilters() {

	return m_filters;

}

void PrintableLogs::ClearLogs() {

	m_logs.clear();
	m_lastCheckedMainLogId = 0;
	m_nextLogId = 0;

}

void PrintableLogs::AddLogs(map<int, LogMessage> newLogs) {

	for(map<int, LogMessage>::iterator newLogsIt = newLogs.begin() ; newLogsIt != newLogs.end() ; ++newLogsIt)
	{
		m_logs[m_nextLogId++] = (*newLogsIt).second;
	}

}

map<int, LogMessage> PrintableLogs::GetLogs() {

	return m_logs;

}

int PrintableLogs::GetLastCheckedMainLogId() {

	return m_lastCheckedMainLogId;

}

void PrintableLogs::SetLastCheckedMainLogId(int newIdVal) {

	m_lastCheckedMainLogId = newIdVal;

}
