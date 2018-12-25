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

class Request
{
public:
	virtual ~Request();
	virtual string GetRequest() = 0;
	virtual void HandleReply(string reply) = 0;
};

#endif /* CLIENT_REQUESTS_REQUEST_H_ */
