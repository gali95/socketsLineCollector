/*
 * LogMessage.cc
 *
 *  Created on: Jan 6, 2019
 *      Author: temp
 */

#include "LogMessage.h"

LogMessage::LogMessage(vector<string> tags, string message):
m_tags(tags),
m_message(message)
{

	m_creationTime = time(&m_creationTime);

}

LogMessage::LogMessage() {
}

string LogMessage::ToString() const{

	string logMessage = "";

	int timeStampMaxSize = 9;
	struct tm * timeinfo;
	char timeStamp [timeStampMaxSize];

	timeinfo = localtime (&m_creationTime);

	strftime (timeStamp,timeStampMaxSize,"%T",timeinfo);

	logMessage += "(";
	logMessage += timeStamp;
	logMessage += ")";

	logMessage += "[";
	for(string tag: m_tags)
	{
		logMessage += tag + " ";
	}
	logMessage += "] " + m_message;

	return logMessage;

}
