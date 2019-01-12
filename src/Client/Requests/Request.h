/*
 * Request.h
 *
 *  Created on: Dec 20, 2018
 *      Author: temp
 */

#ifndef CLIENT_REQUESTS_REQUEST_H_
#define CLIENT_REQUESTS_REQUEST_H_

#include <string>

using namespace std;

class LineCollectorClient;

class Request
{
public:
	virtual string GetRequest() = 0;
	virtual void HandleReply(string reply) = 0;
	LineCollectorClient*& getOwner();
	void setOwner(LineCollectorClient* owner);

protected:
	LineCollectorClient *m_owner;
};

inline LineCollectorClient*& Request::getOwner(){
	return m_owner;
}

inline void Request::setOwner(LineCollectorClient* owner) {
	this->m_owner = owner;
}

#endif /* CLIENT_REQUESTS_REQUEST_H_ */
