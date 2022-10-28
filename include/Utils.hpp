#pragma once

#include <set>
#include <map>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdexcept>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <stdio.h>
#include <fcntl.h>
#include <ctime>
#include <fstream>
#include <signal.h>
#include <algorithm>
#include <Request.hpp>

#define BUFFER_SIZE 512
#define COM_QUERY 3
#define COM_STM_PREPARE 22

using namespace std;

int Socket(int domain, int type, int protocol);
int Bind(int socket, const struct sockaddr *address,
		 socklen_t address_len);
int Listen(int socket, int backlog);
int Accept(int socket, struct sockaddr *address,
		   socklen_t *address_len);
int Connect(int socket, struct sockaddr *address,
			socklen_t address_len);
int Inet_aton(const char *cp, struct in_addr &inp);
int Inet_pton(int af, const char *src, void *dst);
void init_adr(struct sockaddr_in &adr, int port);
void Fcntl(int fd);

void Recv(int fd, ssize_t &bufread, int wfd);
void Send(int fd, ssize_t &send_byte, int rfd);

void sigHendler(int signum);
void createLog(char *str);

void Pipe(int *fd);

vector<string>	split(string & line, string delimiter);
