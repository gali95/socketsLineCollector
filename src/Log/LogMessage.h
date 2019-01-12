/*
 * LogMessage.h
 *
 *  Created on: Jan 6, 2019
 *      Author: temp
 */

#ifndef LOG_LOGMESSAGE_H_
#define LOG_LOGMESSAGE_H_

#include <string>
#include <vector>

using namespace std;

struct LogMessage
{

	LogMessage();
	LogMessage(vector<string> tags, string message);

	vector<string> m_tags;
	string m_message;
	time_t m_creationTime;

	string ToString() const;

};

#endif /* LOG_LOGMESSAGE_H_ */
