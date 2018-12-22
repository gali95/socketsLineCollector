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

using namespace std;

class Logger
{
public:

	static Logger* GetLogger();

	void Log(vector<string> tags,string message);
	void Log(vector<string> tags,const char *message);
private:
	Logger();  // temporary, default constructor can be blocked/removed in better way later
	void PrintLog(vector<string> tags,string message);

	string wholeBuffer;
	static Logger* singleton;
};



#endif /* LOG_LOGGER_H_ */
