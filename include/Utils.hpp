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
#include <ctime>
#include <fstream>
#include <signal.h>
#include <algorithm>

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
int Inet_aton(const char *cp, struct in_addr &inp);
int Inet_pton(int af, const char *src, void *dst);
void init_adr(struct sockaddr_in &adr, int port);
void Fcntl(int fd);

void Recv(int fd, ssize_t &nread, char *res);
void Send(int fd, char *msg, ssize_t &send_byte);

int containsSql(string str);
void createLog(string str, string ip, string port);

void sigHendler(int signum);

void Memcpy(char *dst, const char *src, ssize_t n, ssize_t &byte);
