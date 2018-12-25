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
#include "../Lines/LineCollection.h"
#include "../Config/LineCollectorConfigCollection.h"

class LineCollectorLogic
{

public:

	LineCollectorLogic(LineCollectorConfigCollection config);

	bool Start();
	bool Stop();

	void GetLinesInOrder();
	void GetListOfDiscoveredLineCollectors();
	void GetSendInfo();
	void GetReceivedInfo();
	void GetLogs(vector<string> requiredTags, vector<string> excludedTags);

private:
	LineCollectorClientManager m_clientManager;
	LineSharingServerManager m_serverManager;
	LineCollection m_lineCollection;

};

#endif /* LINECOLLECTORLOGIC_LINECOLLECTORLOGIC_H_ */
