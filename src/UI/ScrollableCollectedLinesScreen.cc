/*
 * ScrollableCollectedLinesScreen.cc
 *
 *  Created on: Jan 11, 2019
 *      Author: temp
 */

#include "ScrollableCollectedLinesScreen.h"
#include "../LineCollectorLogic/LineCollectorLogic.h"

bool ScrollableCollectedLinesScreen::PointToFirstMessage() {

	LineCollection& collection = (*(LineCollectorLogic::LineCollectorLogicSingleton)).GetLineCollection();
	map<int,string> &lines = collection.GetLines();

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

bool ScrollableCollectedLinesScreen::PointToNextMessage() {

	LineCollection& collection = (*(LineCollectorLogic::LineCollectorLogicSingleton)).GetLineCollection();
	map<int,string> &lines = collection.GetLines();

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

string ScrollableCollectedLinesScreen::GetMessage() {

	return to_string((*m_messagePointer).first) + " - " + (*m_messagePointer).second;

}
