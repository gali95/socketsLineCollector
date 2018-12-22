/*
 * StringCapability.h
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */

#ifndef SERVER_CAPABILITIES_STRINGCAPABILITY_H_
#define SERVER_CAPABILITIES_STRINGCAPABILITY_H_

#include <string>

using namespace std;

class StringCapability
{
public:

	virtual ~StringCapability();
	virtual bool CanHandleString(string request) = 0;
	virtual string HandleString(string request) = 0;
};

#endif /* SERVER_CAPABILITIES_STRINGCAPABILITY_H_ */
