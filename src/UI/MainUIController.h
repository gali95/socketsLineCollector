/*
 * MainUIController.h
 *
 *  Created on: Jan 12, 2019
 *      Author: temp
 */

#ifndef UI_MAINUICONTROLLER_H_
#define UI_MAINUICONTROLLER_H_

#include <vector>

#include "ScrollableTextScreenI.h"

class MainUIController
{
public:

	void StartThread();
	void StopThread();

	void PreviousMenu();
	void NextMenu();

private:

	static void* MainLoop(void *thispointer);
	void MainLoop();

	void PrepareMenus();
	void ApplyInput();
	void SlideShow();

	void ClearScreen();

	vector<ScrollableTextScreenI*> m_menus;
	vector<ScrollableTextScreenI*>::iterator m_selectedMenu;

	bool m_endLoop;

	pthread_attr_t m_attr;
	pthread_t m_controllerThread;

};

#endif /* UI_MAINUICONTROLLER_H_ */
