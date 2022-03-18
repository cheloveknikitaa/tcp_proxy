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
	fd_set rfds;
	while (1) {
		rfds = _FdsSet;
		select(_MaxFd + 1, &rfds, NULL, NULL, NULL);
		if (FD_ISSET(_server, &rfds)){
			newConnection();
		}
		for(std::vector<Client *>::iterator Client = _Clients.begin();
			Client != _Clients.end(); ++Client) {
			try {
				(*Client)->recv_send(rfds);
			} catch (int fd) {
				FD_CLR(fd, &_FdsSet);
				FD_CLR((*Client)->getDb(), &_FdsSet);
				delete(*Client);
				Client = _Clients.erase(Client);
			} catch (std::exception &e) { throw e; }
			if (Client == _Clients.end())
				break;
		}
	}
}

void Server::newConnection(){
	int const UserFd = Accept(_server, NULL, NULL);
	if (UserFd >= 0) {
		fcntl(UserFd, F_SETFD, O_NONBLOCK);
		Client *newClient = new Client(UserFd);
		_Clients.push_back(newClient);
		cout << "Connected!\n";
		FD_SET(UserFd, &_FdsSet);
		FD_SET(newClient->getDb(), &_FdsSet);
		_MaxFd = max(_MaxFd, max(UserFd, newClient->getDb()));
	}
}

Server::~Server() {
	for(std::vector<Client *>::iterator Client = _Clients.begin();
		Client != _Clients.end(); ++Client) {
		delete (*Client);
		Client = _Clients.erase(Client);
		if (Client == _Clients.end())
			break;
	}
	close(_server);
}
