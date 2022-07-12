#pragma once

#include "Utils.hpp"

class Server {
private:
	int _socket;
	set<Location&> _locations;
	string _root;
	string _server_name;
	int _port = 80; //?
public:
	void add_locations(Location &);
	Location &find_locations(string &);
	int get_socket();
	Server(int port);
	~Server();
};
