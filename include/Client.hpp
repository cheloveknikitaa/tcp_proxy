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
public:
	Client(int fd);
	Client(int fd, string ip, int port);
	~Client();

	void recv_send(fd_set &rfds);
};
