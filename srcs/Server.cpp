#include "Server.hpp"

Server::Server(int port)
{
	_server = Socket(AF_INET, SOCK_STREAM, 0);
	_MaxFd = _server;
	struct sockaddr_in adr;
	FD_ZERO(&_FdsSet);
	FD_SET(_server, &_FdsSet);
	init_adr(adr, port);
	Bind(_server, (struct sockaddr *)&adr, sizeof adr);
	Listen(_server, 5);
	Fcntl(_server);
}

void Server::run(){
	std::cout << "Waiting for a connection..." << '\n';
	fd_set rfds, wfds;
	while (1) {
		cout << "here\n";
		rfds = _FdsSet;
		//GetConnectionPart
		select(_MaxFd + 1, &rfds, NULL, NULL, NULL);
		if (FD_ISSET(_server, &rfds)){
			newConnection();
		}
		for(std::vector<Client *>::iterator Client = _Clients.begin();
			Client != _Clients.end(); ++Client) {
			(*Client)->recv_send(rfds, wfds);
		}

	}
}

void Server::newConnection(){
	int const UserFd = Accept(_server, NULL, NULL);
	if (UserFd >= 0) {
		fcntl(UserFd, F_SETFD, O_NONBLOCK);
		FD_SET(UserFd, &_FdsSet);
		Client *newClient = new Client(UserFd);
		_Clients.push_back(newClient);
		cout << "Connected!\n";
		_MaxFd = max(_MaxFd, max(UserFd, newClient->getDb()));
	}
}

Server::~Server() {}
