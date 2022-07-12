#pragma once

#include "Utils.hpp"

using namespace std;

class Client {
private:
	int _fd; //socket
	int _toUser[2];
	int _fromUser[2];
	ssize_t _byteFrom = 0;
	ssize_t _byteTo = 0;
	Server &_server;
public:
	Client(int fd, Server &server);
	~Client();

	void recv_send(fd_set &rfds);
};
