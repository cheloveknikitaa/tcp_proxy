#pragma once

#include "Utils.hpp"
#define BUFFER_SIZE 512

using namespace std;

class Client {
private:
	int _db; //socket
	int _fd; //socket
	int _portDb;
	string _ipDb;
	int _toUser[2];
	int _fromUser[2];
	bool _registred;
	ssize_t _byteFrom = 0;
	ssize_t _byteTo = 0;
public:
	Client(int fd);
	Client(int fd, string ip, int port);
	~Client();
	int getDb();

	void connection(fd_set &_FdsSet);

	void recv_send(fd_set &rfds, fd_set &_FdsSet);

	void ConnectToDB();
};
