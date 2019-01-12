/*
 * PrintableLogs.h
 *
 *  Created on: Jan 8, 2019
 *      Author: temp
 */

#ifndef LOG_PRINTABLELOGS_H_
#define LOG_PRINTABLELOGS_H_

#include <vector>
#include <map>
#include <string>

#include "LogMessage.h"

class PrintableLogs
{
public:
	PrintableLogs();
	void SetFilters(vector<string> filters);
	vector<string> GetFilters();
	void ClearLogs();
	void AddLogs(map<int,LogMessage> newLogs);
	map<int,LogMessage> GetLogs();
	int GetLastCheckedMainLogId();
	void SetLastCheckedMainLogId(int newIdVal);
private:
	map<int,LogMessage> m_logs;
	vector<string> m_filters;
	int m_lastCheckedMainLogId;
	int m_nextLogId;
};

#endif /* LOG_PRINTABLELOGS_H_ */
