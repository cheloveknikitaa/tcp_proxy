#pragma once

#include </usr/include/mysql/mysql.h>
#include <iostream>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cerrno>
#include <limits>
#include <sstream>

#include "Client.hpp"

class Client;

using namespace std;

#define SIZE 512

class Server {
private:
	bool _LoopListen;
	int _Sockfd;
	addrinfo *_ServInfo;
	socklen_t _Socklen;
	fd_set _FdsSet;
	int _MaxFd;
	vector<Client *> _Clients;
	Server();
public:
	Server(char *port);
	~Server();

	void run();
	void reader_client();
	void send_client();
	void processCmd(Client *Client);
	void query(Client *Client);
};
