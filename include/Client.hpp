#pragma once

#include "Utils.hpp"
#include "Server.hpp"

using namespace std;

class Client {
private:
	int _fd; //socket
	int _toUser[2];
	int _fromUser[2];
	ssize_t _byteFrom;
	ssize_t _byteTo;
	Server &_server;
public:
	Client(int fd, Server &server);
	~Client();

	void recv_send(fd_set &rfds);
};
