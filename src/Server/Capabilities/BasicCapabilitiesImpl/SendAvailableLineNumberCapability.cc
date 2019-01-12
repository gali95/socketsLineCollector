/*
 * SendAvailableLineNumberCapability.cc
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#include "SendAvailableLineNumberCapability.h"
#include "../../../CollectedData/Lines/LineCollection.h"
#include "../../LineSharingServer.h"

bool SendAvailableLineNumberCapability::CanHandleString(string request) {

	if((m_owner->getLineCollection()->GetNumOfShareableLine()) == -1)
	{
		return false;
	}
	return request=="A";

}

string SendAvailableLineNumberCapability::HandleString(string request) {

	return std::string(1,m_owner->getLineCollection()->GetNumOfShareableLine());

}
