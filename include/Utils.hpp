#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdexcept>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <stdio.h>
#include <fcntl.h>
#include "Client.hpp"
#include <vector>


#define BUFFER_SIZE 512

using namespace std;

int Socket(int domain, int type, int protocol);
int Bind(int socket, const struct sockaddr *address,
		 socklen_t address_len);
int Listen(int socket, int backlog);
int Accept(int socket, struct sockaddr *address,
		   socklen_t *address_len);
int Connect(int socket, struct sockaddr *address,
			socklen_t address_len);
int Inet_pton(int af, const char *src, void *dst);

void init_adr(struct sockaddr_in &adr, int port);

void Fcntl(int fd);

string Recv(int fd);
void Send(int fd, string msg);
