#pragma once

#include "Utils.hpp"

class Server {
private:
	int _server;
	vector<Client *> _Clients;
	int _MaxFd;
	fd_set _FdsSet;
	string _ip;
	int _port;
public:
	Server(int port);
	Server(string ip, int portDb, int port);
	~Server();
	void run();

	void newConnection();
};
