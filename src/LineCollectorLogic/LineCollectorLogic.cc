/*
 * LineCollectorLogic.cc
 *
 *  Created on: Dec 24, 2018
 *      Author: temp
 */

#include "LineCollectorLogic.h"

bool LineCollectorLogic::Start() {

	m_serverManager.StartThreads();
	m_clientManager.StartThreads();

}

bool LineCollectorLogic::Stop() {

	m_serverManager.StopThreads();
	m_clientManager.StopThreads();

}

void LineCollectorLogic::GetLinesInOrder() {
}

void LineCollectorLogic::GetListOfDiscoveredLineCollectors() {
}

void LineCollectorLogic::GetSendInfo() {
}

void LineCollectorLogic::GetReceivedInfo() {
}

void LineCollectorLogic::GetLogs(vector<string> requiredTags,
		vector<string> excludedTags) {
}

LineCollectorLogic::LineCollectorLogic(LineCollectorConfigCollection config):
m_clientManager(config.m_threadConfig, config.m_networkConfig),
m_serverManager(config.m_threadConfig, config.m_networkConfig)
{
	m_lineCollection.AddShareableLine(config.m_lineToShareConfig.getLineNumber(),
									  config.m_lineToShareConfig.getLine());
}
