#pragma once

#include "Utils.hpp"

class Server {
private:
	int _server;
	vector<Client *> _Clients;
	int _MaxFd, _MaxDbFd;
	fd_set _FdsSet;
public:
	Server(int port);
	~Server();
	void run();
};
