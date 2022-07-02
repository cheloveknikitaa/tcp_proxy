#pragma once

#include "Utils.hpp"

class Server {
private:
	int _server;
	vector<Client *> _Clients;
	int _MaxFd;
	fd_set _FdsSet;
public:
	Server(int port);
	~Server();
	void run();

	void newConnection();
};
