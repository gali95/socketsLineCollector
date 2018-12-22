/*
 * Log.cc
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */
#include <iostream>

#include "Logger.h"

using namespace std;

Logger* Logger::singleton = NULL;

Logger* Logger::GetLogger()
{
	if(!singleton)
	{
		singleton = new Logger();
	}
	return singleton;
}

void Logger::Log(vector<string> tags,string message)
{
	PrintLog(tags,message);
}

void Logger::Log(vector<string> tags,const char *message)
{
	Log(tags,static_cast<string>(message));
}

Logger::Logger()
{

}

void Logger::PrintLog(vector<string> tags,string message)
{
	cout << "[";
	for(string tag: tags)
	{
		cout << tag << " ";
	}
	cout << "] " << message << endl;
}


