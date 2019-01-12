/*
 * ScrollableTextScreenI.cc
 *
 *  Created on: Jan 10, 2019
 *      Author: temp
 */

#include <iostream>

#include "ScrollableTextScreenI.h"

using namespace std;

void ScrollableTextScreenI::CoutScreenContentWrapper() {

	if(m_autoScroolDown)
	{
		m_indexOfTopLine = GetMaxNumberOfTopLine();
	}
	CoutScreenContent();
}

void ScrollableTextScreenI::LineUp() {

	if(m_indexOfTopLine > 0)
	{
		m_indexOfTopLine--;
		m_autoScroolDown = false;
	}

}

void ScrollableTextScreenI::LineDown() {

	m_indexOfTopLine++;

	int maxIndex = GetMaxNumberOfTopLine();

	if(m_indexOfTopLine > maxIndex)
	{
		m_indexOfTopLine = maxIndex;
	}
	else
	{
		m_autoScroolDown = false;
	}

}

ScrollableTextScreenI::~ScrollableTextScreenI() {

}

void ScrollableTextScreenI::CoutScreenContent() {


	int printedMessages = 0;
	int remainingSkips = m_indexOfTopLine;

	if(!PointToFirstMessage())
	{
		return;
	}

	while(remainingSkips > 0)
	{
		remainingSkips--;
		if(!PointToNextMessage())
		{
			return;
		}
	}

	do
	{
		cout << GetMessage() << endl;
		printedMessages++;

	} while ((PointToNextMessage()) && (printedMessages < m_linesNumber));
}

void ScrollableTextScreenI::AutoScroll() {

	m_autoScroolDown = true;

}

int ScrollableTextScreenI::GetMaxNumberOfTopLine() {

	int numberOfMessagesInLog = 0;

	if(!PointToFirstMessage())
	{
		return 0;
	}

	numberOfMessagesInLog++;

	while(PointToNextMessage())
	{
		numberOfMessagesInLog++;
	}

	int maxNumberOfTopLine = numberOfMessagesInLog - m_linesNumber;

	if(maxNumberOfTopLine < 0)
	{
		maxNumberOfTopLine = 0;
	}

	return maxNumberOfTopLine;

}
