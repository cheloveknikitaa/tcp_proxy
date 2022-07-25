#pragma once

#include "Utils.hpp"
#include "Client.hpp"
using namespace std;
class Core
{
private:
	int _MaxFd;
	fd_set _FdsSet;
	vector<Client *> _Clients;
	map<int, Server> _servers;
public:
	void run();
	void newConnection(Server &server);

	Core(string path_to_config = "default");
	~Core();
};
