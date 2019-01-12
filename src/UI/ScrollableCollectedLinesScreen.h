/*
 * ScrollableCollectedLinesScreen.h
 *
 *  Created on: Jan 11, 2019
 *      Author: temp
 */

#ifndef UI_SCROLLABLECOLLECTEDLINESSCREEN_H_
#define UI_SCROLLABLECOLLECTEDLINESSCREEN_H_

#include <map>

#include "ScrollableTextScreenI.h"

class ScrollableCollectedLinesScreen : public ScrollableTextScreenI
{
public:

private:

	bool PointToFirstMessage() override;
	bool PointToNextMessage() override;
	string GetMessage() override;

	map<int,string>::const_iterator m_messagePointer;
};

#endif /* UI_SCROLLABLECOLLECTEDLINESSCREEN_H_ */
