#include "Server.hpp"

Server::Server(int port)
{
	_socket = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr;
	init_adr(adr, port);
	Bind(_socket, (struct sockaddr *)&adr, sizeof adr);
	Listen(_socket, 5);
	Fcntl(_socket);
}

Server::~Server() {
	close(_socket);
}
