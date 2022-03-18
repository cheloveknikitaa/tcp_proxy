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
public:
	Client(int fd);

	~Client();
	int getDb();

	void connection();

	void recv_send(fd_set &rfds, fd_set &wfds);

	void ConnectToDB();
};
