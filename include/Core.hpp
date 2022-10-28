#pragma once

#include "Utils.hpp"
#include "Client.hpp"
#include "Parser.hpp"

using namespace std;

class Parser;
class Core
{
private:
	int _MaxFd;
	fd_set _FdsSet;
	vector<Client *> _Clients;
	map<int, Server *> _servers;
public:
	void run();
	void newConnection(Server &server);

	Core(const string &path_to_config = "default");
	~Core();
};
