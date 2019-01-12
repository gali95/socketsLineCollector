/*
 * ScrollableLogScreen.cc
 *
 *  Created on: Jan 9, 2019
 *      Author: temp
 */

#include <iostream>

#include "ScrollableLogScreen.h"
#include "../Log/Logger.h"

using namespace std;

void ScrollableLogScreen::SetFilters(vector<string> mustHaveTags) {

	m_mustHaveTags = mustHaveTags;

}

bool ScrollableLogScreen::PointToFirstMessage() {

	const map<int,LogMessage>& logs = Logger::GetLogger()->GetLogs();

	for(m_messagePointer = logs.begin() ; m_messagePointer != logs.end() ; ++m_messagePointer)
	{
		if(LogContainsEveryTag((*m_messagePointer).second,m_mustHaveTags))
		{
			m_messagePointerId = 0;
			return true;
		}
	}
	return false;

}

bool ScrollableLogScreen::PointToNextMessage() {

	const map<int,LogMessage>& logs = Logger::GetLogger()->GetLogs();

	if(m_messagePointer == logs.end())
	{
		return false;
	}

	for(++m_messagePointer ; m_messagePointer != logs.end() ; ++m_messagePointer)
	{
		if(LogContainsEveryTag((*m_messagePointer).second,m_mustHaveTags))
		{
			m_messagePointerId++;
			return true;
		}
	}
	return false;

}

string ScrollableLogScreen::GetMessage() {

	return "<" + to_string(m_messagePointerId) + ">" + (*m_messagePointer).second.ToString();

}

bool ScrollableLogScreen::LogContainsEveryTag(LogMessage log,
		vector<string> tags) {

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
