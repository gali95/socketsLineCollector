/*
 * LineCollectorLogic.cc
 *
 *  Created on: Dec 24, 2018
 *      Author: temp
 */

#include "LineCollectorLogic.h"

LineCollectorLogic *LineCollectorLogic::LineCollectorLogicSingleton;

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
m_clientManager(config.m_threadConfig, config.m_networkConfig, &m_lineCollection),
m_serverManager(config.m_threadConfig, config.m_networkConfig, &m_lineCollection)
{
	m_lineCollection.AddShareableLine(config.m_lineToShareConfig.getLineNumber(),
									  config.m_lineToShareConfig.getLine());
}

LineCollectorLogic::LineCollectorLogic(const LineCollectorLogic& old_obj):
m_clientManager(old_obj.m_clientManager),
m_serverManager(old_obj.m_serverManager),
m_lineCollection(old_obj.m_lineCollection)
{
	m_clientManager.SetLineCollection(&m_lineCollection);
	m_serverManager.SetLineCollection(&m_lineCollection);
}

LineCollection& LineCollectorLogic::GetLineCollection() {

	return m_lineCollection;
}
