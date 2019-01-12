/*
 * StringCapability.h
 *
 *  Created on: Dec 16, 2018
 *      Author: temp
 */

#ifndef SERVER_CAPABILITIES_STRINGCAPABILITY_H_
#define SERVER_CAPABILITIES_STRINGCAPABILITY_H_

#include <string>

class LineSharingServer;

using namespace std;

class StringCapability
{
public:

	virtual bool CanHandleString(string request) = 0;
	virtual string HandleString(string request) = 0;
	LineSharingServer*& getOwner();
	void setOwner(LineSharingServer* owner);

protected:
	LineSharingServer *m_owner;
};

inline LineSharingServer*& StringCapability::getOwner() {
	return m_owner;
}

inline void StringCapability::setOwner(LineSharingServer* owner) {
	m_owner = owner;
}

#endif /* SERVER_CAPABILITIES_STRINGCAPABILITY_H_ */
