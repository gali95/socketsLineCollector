/*
 * AvailableLineRequest.h
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#ifndef CLIENT_REQUESTS_BASICREQUESTSIMPL_AVAILABLELINEREQUEST_H_
#define CLIENT_REQUESTS_BASICREQUESTSIMPL_AVAILABLELINEREQUEST_H_

#include "../Request.h"

class AvailableLineRequest : public Request
{
public:
	virtual string GetRequest() override;
	virtual void HandleReply(string reply) override;
};

#endif /* CLIENT_REQUESTS_BASICREQUESTSIMPL_AVAILABLELINEREQUEST_H_ */
