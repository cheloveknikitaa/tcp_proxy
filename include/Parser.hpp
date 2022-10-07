#pragma once
//#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// enum methods
// {
//     GET,
//     POST,
//     PUT,
//     DELETE
// };

//Любой серверный блок, не включающий директиву listen, по умолчанию имеет параметры прослушивания 0.0.0.0:80

struct ListenPort {
	string _host;
	string _port;
	bool	isDefault;
};

struct Cgi {

};

class Location {
	string _errorPage;
	string _root;
	unsigned int _clientMaxBodySize;
	string	_method;
	string	_path;
	Cgi		_cgi;
};

class Serv
{
	private:
	vector <ListenPort> _listenPort;
	vector <string> _serverName;
	vector <Location> locations;
};

class Parser
{
private:
	vector <Serv> servers;
public:
	Parser(void) {};
	void	parse(const string &filename);
	~Parser() {};
};

