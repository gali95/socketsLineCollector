/*
 * LineCollectorLogic.h
 *
 *  Created on: Dec 23, 2018
 *      Author: temp
 */

#ifndef LINECOLLECTORLOGIC_LINECOLLECTORLOGIC_H_
#define LINECOLLECTORLOGIC_LINECOLLECTORLOGIC_H_

#include "../Client/Manager/LineCollectorClientManager.h"
#include "../Server/Manager/LineSharingServerManager.h"
#include "../CollectedData/Lines/LineCollection.h"
#include "../Config/LineCollectorConfigCollection.h"

class LineCollectorLogic
{

public:

	static LineCollectorLogic *LineCollectorLogicSingleton;

	LineCollectorLogic(LineCollectorConfigCollection config);
	LineCollectorLogic (const LineCollectorLogic &old_obj);

	bool Start();
	bool Stop();

	void GetLinesInOrder();  // DONE, those functions make no sense but are good TODO list :D
	void GetListOfDiscoveredLineCollectors();  // screen to show data done, not tested
	void GetSendInfo();  // screen done, logs put in place, refactor log string - should sender and/or receiver data be shown?
	void GetReceivedInfo(); // as above
	void GetLogs(vector<string> requiredTags, vector<string> excludedTags);
	LineCollection &GetLineCollection();

private:
	LineCollectorClientManager m_clientManager;
	LineSharingServerManager m_serverManager;
	LineCollection m_lineCollection;

};

#endif /* LINECOLLECTORLOGIC_LINECOLLECTORLOGIC_H_ */
