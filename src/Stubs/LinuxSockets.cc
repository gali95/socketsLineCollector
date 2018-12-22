/*
 * LinuxSockets.cc
 *
 *  Created on: 22 gru 2018
 *      Author: ppp
 */

//// STUBS REPLACING LINUX SOCKET LIBRARIES SO IT CAN BE COMPILED ON WINDOWS

#include "LinuxSockets.h"

using namespace std;


socklen_t::socklen_t(unsigned int e)
{

}
socklen_t::socklen_t()
{

}

int socket(int domain, int type, int protocol)
{
	return 0;
}

struct hostent *gethostbyname(const char *name)
{
	return 0;
}

void bzero(void *s, size_t n)
{

}

void bcopy(const void *src, void *dest, size_t n)
{

}

uint16_t htons(uint16_t hostshort)
{
	return 0;
}

int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen)
{
	return 0;
}

int listen(int sockfd, int backlog)
{
	return 0;
}

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	return 0;
}

int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen)
{
	return 0;
}

