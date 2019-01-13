/*
 * MainUIController.cc
 *
 *  Created on: Jan 13, 2019
 *      Author: temp
 */

#include <iostream>
#include <unistd.h>

#include "MainUIController.h"
#include "ScrollableLogScreen.h"
#include "ScrollableCollectedLinesScreen.h"
#include "ScrollableDiscoveredAppsScreen.h"
#include "KeyboardInputReader.h"
#include "../Config/KeyboardConfig.h"
#include "../Log/Logger.h"

using namespace std;

void MainUIController::ClearScreen()
{
	cout << "\033[2J\033[1;1H";
}

void MainUIController::MainLoop() {

	m_endLoop = false;
	while(!m_endLoop)
	{
		ClearScreen();
		(*m_selectedMenu)->CoutScreenContentWrapper();
		sleep(5);
	}

}

void MainUIController::PrepareMenus() {

	ScrollableLogScreen *logScreen;

	logScreen = new ScrollableLogScreen("READ DATA:");
	logScreen->SetFilters({"socket_read"});
	m_menus.push_back(logScreen);

	logScreen = new ScrollableLogScreen("SEND DATA");
	logScreen->SetFilters({"socket_write"});
	m_menus.push_back(logScreen);

	m_menus.push_back(new ScrollableCollectedLinesScreen("COLLECTED LINES"));
	m_menus.push_back(new ScrollableDiscoveredAppsScreen("DISCOVERED APPLICATIONS"));

	for(vector<ScrollableTextScreenI*>::iterator menusIt = m_menus.begin() ; menusIt != m_menus.end(); ++menusIt)
	{
		(*menusIt)->AutoScroll();
	}
	m_selectedMenu = m_menus.begin();

}

void MainUIController::ApplyInput() {

	if(KeyboardInputReader::isKeyActive())
	{
		char activeKey = KeyboardInputReader::getActiveKey();

		if(KeyboardInputReader::getActiveKeyState() == keyState::hold)
		{
			if(KeyboardInputReader::getActiveKeyHoldTime() > 1)
			{
				if(activeKey == KeyboardConfig::PreviousLine())
				{
					(*m_selectedMenu)->LineUp();
				}
				else if(activeKey == KeyboardConfig::NextLine())
				{
					(*m_selectedMenu)->LineDown();
				}
			}
		}
		else if(KeyboardInputReader::getActiveKeyState() == keyState::released)
		{
			if(activeKey == KeyboardConfig::PreviousLine())
			{
				(*m_selectedMenu)->LineUp();
			}
			else if(activeKey == KeyboardConfig::NextLine())
			{
				(*m_selectedMenu)->LineDown();
			}
			else if(activeKey == KeyboardConfig::FirstLine())
			{
				(*m_selectedMenu)->FirstLine();
			}
			else if(activeKey == KeyboardConfig::AutoScroll())
			{
				(*m_selectedMenu)->AutoScroll();
			}
			else if(activeKey == KeyboardConfig::Exit())
			{
				m_endLoop = true;
			}
			else if(activeKey == KeyboardConfig::NextMenu())
			{
				NextMenu();
			}
			else if(activeKey == KeyboardConfig::PreviousMenu())
			{
				PreviousMenu();
			}
		}
	}

}

void MainUIController::PreviousMenu() {

	if(m_selectedMenu == m_menus.begin())
	{
		m_selectedMenu = m_menus.end();
		m_selectedMenu--;
	}
	else
	{
		m_selectedMenu--;
	}

	ClearScreen();
			(*m_selectedMenu)->CoutScreenContentWrapper();
}

void MainUIController::SlideShow() {

	NextMenu();

}

void MainUIController::StartThread() {

	PrepareMenus();

	void *status;
	int pthreadResult;

	pthread_attr_init(&m_attr);
	pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);


	pthreadResult = pthread_create(&m_controllerThread, NULL, &MainLoop, (void*)this);
	if(pthreadResult)
	{
		Logger::GetLogger()->Log({"error"},"Error: failed to create server thread");
	}

}

void MainUIController::StopThread() {

	void *status;
	int pthreadResult;

	m_endLoop = true;

	pthread_attr_destroy(&m_attr);

	pthreadResult = pthread_join(m_controllerThread, &status);
	if (pthreadResult) {
		Logger::GetLogger()->Log({"error"},"Error: server thread unable to join,");
	}

}

void* MainUIController::MainLoop(void* nothing) {

	((MainUIController*)nothing)->MainLoop();

}

void MainUIController::NextMenu() {

	m_selectedMenu++;

	if(m_selectedMenu == m_menus.end())
	{
		m_selectedMenu = m_menus.begin();
	}

	ClearScreen();
			(*m_selectedMenu)->CoutScreenContentWrapper();
}
