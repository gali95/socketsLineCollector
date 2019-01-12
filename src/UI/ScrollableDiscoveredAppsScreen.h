/*
 * ScrollableDiscoveredAppsScreen.h
 *
 *  Created on: Jan 12, 2019
 *      Author: temp
 */

#ifndef UI_SCROLLABLEDISCOVEREDAPPSSCREEN_H_
#define UI_SCROLLABLEDISCOVEREDAPPSSCREEN_H_

#include <map>

#include "ScrollableTextScreenI.h"
#include "../CollectedData/DiscoveredApplicationsInfo/DiscoveredApplicationStruct.h"

class ScrollableDiscoveredAppsScreen : public ScrollableTextScreenI
{
public:

private:

	bool PointToFirstMessage() override;
	bool PointToNextMessage() override;
	string GetMessage() override;

	map<pair<string,int>,DiscoveredApplicationStruct>::const_iterator m_messagePointer;
};



#endif /* UI_SCROLLABLEDISCOVEREDAPPSSCREEN_H_ */
