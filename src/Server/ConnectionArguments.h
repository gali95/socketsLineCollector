/*
 * ConnectionArguments.h
 *
 *  Created on: Dec 18, 2018
 *      Author: temp
 */

#ifndef SERVER_CONNECTIONARGUMENTS_H_
#define SERVER_CONNECTIONARGUMENTS_H_

class LineSharingServer;

struct ConnectionArguments
{
	LineSharingServer *m_server;
	int m_newsockfd;

    ConnectionArguments(LineSharingServer* server, int newsockfd):
    m_server(server),
	m_newsockfd(newsockfd)
	{

	}
};

#endif /* SERVER_CONNECTIONARGUMENTS_H_ */
