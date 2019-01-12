/*
 * Log.h
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */

#ifndef LOG_LOGGER_H_
#define LOG_LOGGER_H_

#include <vector>
#include <string>
#include <map>

#include "LogMessage.h"
#include "PrintableLogs.h"

using namespace std;

class Logger
{
public:

	static Logger* GetLogger();

	void Log(vector<string> tags,string message);
	void Log(vector<string> tags,const char *message);

	map<int,LogMessage>& GetLogs();

	void UpdatePrintableLog(PrintableLogs &log);
private:
	Logger();  // temporary, default constructor can be blocked/removed in better way later
	void PrintLog(LogMessage logMessage);
	void StoreLog(LogMessage logMessage);

	map<int,LogMessage> GetLogsContainingEveryListedTags(vector<string> tags);
	bool LogContainsEveryTag(LogMessage log, vector<string> tags);

	static Logger* singleton;
	pthread_mutex_t	m_logging_mutex;
	pthread_mutex_t m_storeLog_mutex;
	map<int,LogMessage> m_logs;
	unsigned int m_nextStoredLogId;
};



#endif /* LOG_LOGGER_H_ */
