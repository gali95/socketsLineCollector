/*
 * ScrollableTextScreenI.h
 *
 *  Created on: Jan 10, 2019
 *      Author: temp
 */

#ifndef UI_SCROLLABLETEXTSCREENI_H_
#define UI_SCROLLABLETEXTSCREENI_H_

#include <string>

using namespace std;

class ScrollableTextScreenI
{
public:

	virtual ~ScrollableTextScreenI();

	void CoutScreenContentWrapper();
	virtual void CoutScreenContent();

	void LineUp();
	void LineDown();
	void AutoScroll();

protected:

	virtual bool PointToFirstMessage() = 0;
	virtual bool PointToNextMessage() = 0;
	virtual string GetMessage() = 0;

	int m_linesNumber = 10;
	int m_indexOfTopLine = 0;

private:

	int GetMaxNumberOfTopLine();

	bool m_autoScroolDown = false;
};

#endif /* UI_SCROLLABLETEXTSCREENI_H_ */
