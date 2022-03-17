#pragma once

#include "Utils.hpp"

class Client {
private:
	int _db;
	int _fd;
	int _portDb;
	std::string _ipDb;
public:
	Client(int fd);
	~Client();
};
