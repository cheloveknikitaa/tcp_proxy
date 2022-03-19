#pragma once

#include "Utils.hpp"
#define BUFFER_SIZE 512

using namespace std;

class Client {
private:
	int _db;
	int _fd;
	string _portDb;
	string _ipDb;
	char _bufferFromClient[BUFFER_SIZE] { 0 };
	char _bufferToClient[BUFFER_SIZE] { 0 };
	bool _registred;
	ssize_t _byteFrom = 0;
	ssize_t _byteTo = 0;
public:
	Client(int fd);

	~Client();
	int getDb();

	void connection(fd_set &_FdsSet);

	void recv_send(fd_set &rfds, fd_set &_FdsSet);

	void ConnectToDB();
};
