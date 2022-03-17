#pragma once

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

	int _Sockfd { -1 };
	addrinfo *_ServInfo { NULL };
	socklen_t _Socklen { 0 };
	fd_set _FdsSet;
	int _MaxFd { 0 };
	int _MaxDbFd { 0 };
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
