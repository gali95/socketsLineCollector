/*
 * Log.cc
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */
#include <iostream>
#include <algorithm>

#include "Logger.h"

using namespace std;

Logger* Logger::singleton = NULL;

Logger* Logger::GetLogger()
{
	if(!singleton)
	{
		singleton = new Logger();
		singleton->m_logging_mutex = PTHREAD_MUTEX_INITIALIZER;
		singleton->m_storeLog_mutex = PTHREAD_MUTEX_INITIALIZER;
	}
	return singleton;
}

void Logger::Log(vector<string> tags,string message)
{
	LogMessage logMessage(tags,message);
	StoreLog(logMessage);
	//PrintLog(logMessage);
}

void Logger::Log(vector<string> tags,const char *message)
{
	Log(tags,static_cast<string>(message));
}

Logger::Logger()
{
	m_nextStoredLogId = 1;
}

void Logger::PrintLog(LogMessage logMessage)
{

	if(std::find(logMessage.m_tags.begin(), logMessage.m_tags.end(), "socket_write") == logMessage.m_tags.end() &&
	   std::find(logMessage.m_tags.begin(), logMessage.m_tags.end(), "socket_read") == logMessage.m_tags.end()	)
	{
	    return;
	}


	pthread_mutex_lock(&m_logging_mutex);

	cout << logMessage.ToString() << endl;

	pthread_mutex_unlock(&m_logging_mutex);
}

void Logger::StoreLog(LogMessage logMessage) {

	pthread_mutex_lock(&m_storeLog_mutex);

	m_logs.insert(make_pair(m_nextStoredLogId++,logMessage));

	pthread_mutex_unlock(&m_storeLog_mutex);

}

map<int, LogMessage> Logger::GetLogsContainingEveryListedTags(
		vector<string> tags) {

	map<int, LogMessage> filteredLogs;
	int nextFilteredLogId = 0;

	map<int, LogMessage>::iterator logsIt;

	for(logsIt = m_logs.begin() ; logsIt != m_logs.end() ; ++logsIt)
	{
		if(LogContainsEveryTag((*logsIt).second,tags))
		{
			filteredLogs[nextFilteredLogId++] = (*logsIt).second;
		}
	}

	return filteredLogs;

}

void Logger::UpdatePrintableLog(PrintableLogs& log) {

	map<int, LogMessage> filteredLogs;
	int nextFilteredLogId = 0;

	map<int, LogMessage>::iterator logsIt;
	int lastId;

	for(logsIt = m_logs.find(log.GetLastCheckedMainLogId()+1) ; logsIt != m_logs.end() ; ++logsIt)
	{
		if(LogContainsEveryTag((*logsIt).second,log.GetFilters()))
		{
			filteredLogs[nextFilteredLogId++] = (*logsIt).second;
		}
		lastId = (*logsIt).first;
	}

	log.SetLastCheckedMainLogId(lastId);
	log.AddLogs(filteredLogs);

}

bool Logger::LogContainsEveryTag(LogMessage log, vector<string> tags) {

	for(vector<string>::iterator requiredTagsIt = tags.begin(); requiredTagsIt != tags.end() ; ++requiredTagsIt)
	{
		bool containsRequiredTag = false;
		for(vector<string>::iterator messageTagsIt = log.m_tags.begin(); messageTagsIt != log.m_tags.end() ; ++messageTagsIt)
		{
			if((*messageTagsIt) == (*requiredTagsIt))
			{
				containsRequiredTag = true;
				break;
			}
		}
		if(!containsRequiredTag)
		{
			return false;
		}
	}
	return true;
}

map<int, LogMessage>& Logger::GetLogs() {

	return m_logs;

}
