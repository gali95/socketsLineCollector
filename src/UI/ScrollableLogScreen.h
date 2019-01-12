/*
 * ScrollableLogScreen.h
 *
 *  Created on: Jan 9, 2019
 *      Author: temp
 */

#ifndef UI_SCROLLABLELOGSCREEN_H_
#define UI_SCROLLABLELOGSCREEN_H_

#include <string>

#include "../Log/PrintableLogs.h"
#include "ScrollableTextScreenI.h"

using namespace std;

class ScrollableLogScreen : public ScrollableTextScreenI
{
public:

	void SetFilters(vector<string> mustHaveTags);

private:

	bool PointToFirstMessage() override;
	bool PointToNextMessage() override;
	string GetMessage() override;

	bool LogContainsEveryTag(LogMessage log, vector<string> tags);

	vector<string> m_mustHaveTags;
	map<int,LogMessage>::const_iterator m_messagePointer;
	int m_messagePointerId;

};


#endif /* UI_SCROLLABLELOGSCREEN_H_ */
