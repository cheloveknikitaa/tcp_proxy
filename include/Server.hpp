#pragma once

#include "Utils.hpp"
#include "Location.hpp"

using namespace std;
class Server {
private:
	int _socket;
	vector<Location_t> _locations;
	string _root;
	string _server_name;
	int _port;
public:
	void add_locations(Location &);
	Location &find_locations(string &);
	int get_socket();
	Server(vector<Location_t> locations, string root = "", int port = 80, string server_name = "");
	~Server();
};
