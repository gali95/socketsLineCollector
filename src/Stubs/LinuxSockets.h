/*
 * LinuxSockets.h
 *
 *  Created on: 22 gru 2018
 *      Author: ppp
 */

#ifndef STUBS_LINUXSOCKETS_H_
#define STUBS_LINUXSOCKETS_H_

#include <cstddef>
#include <stdint.h>
#include <string>

#include "LinuxSockets.h"

using namespace std;

#define AF_INET 0
#define SOCK_STREAM 0
#define SOCK_NONBLOCK 0
#define INADDR_ANY 0

struct sin_addr
{
	int s_addr;
};

struct sockaddr_in
{
	int sin_family;
	struct sin_addr sin_addr;
	int sin_port;
};

struct socklen_t
{
	socklen_t(unsigned int e);
	socklen_t();
};

struct hostent
{
	char* h_addr;
	int h_length;
};

int socket(int domain, int type, int protocol);

struct hostent *gethostbyname(const char *name);

void bzero(void *s, size_t n);

void bcopy(const void *src, void *dest, size_t n);

uint16_t htons(uint16_t hostshort);

int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);

int listen(int sockfd, int backlog);

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);

#endif /* STUBS_LINUXSOCKETS_H_ */
