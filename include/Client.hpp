#pragma once

#include "Utils.hpp"

using namespace std;

class Client {
private:
	int _db;
	int _fd;
	string _portDb;
	string _ipDb;
	string _bufferFromClient;
	string _bufferToClient;
	bool _registred;
	ssize_t _byteFrom;
	ssize_t _byteTo;
public:
	Client(int fd);

	~Client();
	int getDb();

	void connection(fd_set &_FdsSet);

	void recv_send(fd_set &rfds, fd_set &_FdsSet);

	void ConnectToDB();
};
