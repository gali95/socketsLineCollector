/*
 * AvailableLineNumberRequest.cc
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#include "AvailableLineNumberRequest.h"
#include "../../../CollectedData/Lines/LineCollection.h"
#include "../../LineCollectorClient.h"
#include "AvailableLineRequest.h"
#include "../../../Log/Logger.h"

string AvailableLineNumberRequest::GetRequest() {

	return string(1, 'A');

}

void AvailableLineNumberRequest::HandleReply(string reply) {

	int availableLine = static_cast<int>(reply[0]);

	if(isReplyCorrect(reply))
	{
		(*m_owner).LogDiscoveredServerData(true);
	}
	else
	{
		(*m_owner).LogDiscoveredServerData(false);
	}

	LineCollection lineCollection = *(m_owner->getLineCollection());
	if(!lineCollection.HasLine(availableLine))
	{
		Request *nextRequest = new AvailableLineRequest(availableLine);
		m_owner->setActiveRequest(nextRequest);
		Logger::GetLogger()->Log({"handleReponse","client"}," This line is needed, changing request to AvailableLine");
	}
	else
	{
		Logger::GetLogger()->Log({"handleReponse","client"}," Client already has this line");
		m_owner->StopCurrentConnection();
	}

}

bool AvailableLineNumberRequest::isReplyCorrect(string reply) {

	if(reply.length() != 1)
	{
		return false;
	}
	if(reply[0] == 0)
	{
		return false;
	}
	if(reply[0] > 50)
	{
		return false;
	}
	return true;

}
