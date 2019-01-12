/*
 * AvailableLineRequest.cc
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#include "AvailableLineRequest.h"
#include "../../../CollectedData/Lines/LineCollection.h"
#include "../../LineCollectorClient.h"
#include "AvailableLineNumberRequest.h"
#include "../../../Log/Logger.h"

AvailableLineRequest::AvailableLineRequest(int lineNumber)
{
	m_lineNumber = lineNumber;
}

string AvailableLineRequest::GetRequest() {

	return string(1, 'B');
}

void AvailableLineRequest::HandleReply(string reply) {

	LineCollection &lineCollection = *(m_owner->getLineCollection());

	lineCollection.AddLine(m_lineNumber,reply);

	Request *nextRequest = new AvailableLineNumberRequest();
	m_owner->setActiveRequest(nextRequest);

	m_owner->StopCurrentConnection();

	Logger::GetLogger()->Log({"handleReponse","client"}," New line has been received");
}
