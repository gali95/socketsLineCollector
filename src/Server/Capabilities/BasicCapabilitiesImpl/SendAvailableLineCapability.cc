/*
 * SendAvailableLineCapability.cc
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#include "SendAvailableLineCapability.h"
#include "../../../CollectedData/Lines/LineCollection.h"
#include "../../LineSharingServer.h"

bool SendAvailableLineCapability::CanHandleString(string request) {

	if((m_owner->getLineCollection()->GetNumOfShareableLine()) == -1)
	{
		return false;
	}
	return request=="B";

}

string SendAvailableLineCapability::HandleString(string request) {

	return m_owner->getLineCollection()->GetShareableLine();

}
