#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdexcept>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <stdio.h>

#define BUFFER_SIZE 512

using namespace std;

class Server {
private:
	int _server;
public:
	Server(int port);
	~Server();
	void run();
};
