#include "Server.hpp"

Server::Server(int port) : _FdsSet()
{
	_MaxFd = 0;
	_MaxDbFd = 0;
	_server = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr;
	init_adr(adr, port);
	Bind(_server, (struct sockaddr *)&adr, sizeof adr);
	Listen(_server, 5);
	Fcntl(_server);
}

void Server::run(){
	std::cout << "Waiting for a connection..." << '\n';
	while (1) {
		//GetConnectionPart
		int const UserFd = Accept(_server, NULL, NULL);
		if (UserFd >= 0) {
			if (UserFd > _MaxFd) {
				_MaxFd = UserFd;
			}
			fcntl(UserFd, F_SETFD, O_NONBLOCK);
			FD_SET(UserFd, &_FdsSet);
			_Clients.push_back(new Client(UserFd));
			cout << "Connected!\n";
		}

	}
//	int fd =
//	ssize_t nread;
//	char buf[BUFFER_SIZE];
//	nread = recv(fd, buf, BUFFER_SIZE, MSG_NOSIGNAL);
//	if (nread == -1) {
//		throw runtime_error(string("Recv: ") + strerror(errno));
//	} else if (nread == 0) {
//
//	}
//	cout << buf << endl;
}

Server::~Server() {}
