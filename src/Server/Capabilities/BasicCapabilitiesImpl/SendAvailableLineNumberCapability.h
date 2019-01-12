/*
 * SendAvailableLineNumberCapability.h
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#ifndef SERVER_CAPABILITIES_BASICCAPABILITIESIMPL_SENDAVAILABLELINENUMBERCAPABILITY_H_
#define SERVER_CAPABILITIES_BASICCAPABILITIESIMPL_SENDAVAILABLELINENUMBERCAPABILITY_H_

#include "../StringCapability.h"

class SendAvailableLineNumberCapability : public StringCapability
{
	virtual bool CanHandleString(string request) override;
	virtual string HandleString(string request) override;
};

#endif /* SERVER_CAPABILITIES_BASICCAPABILITIESIMPL_SENDAVAILABLELINENUMBERCAPABILITY_H_ */
