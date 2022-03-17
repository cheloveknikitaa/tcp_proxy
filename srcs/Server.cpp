#include "Server.hpp"

Server::Server(int port)
{
	_server = socket(AF_INET, SOCK_STREAM, 0);
	if (_server == -1) {
		throw runtime_error(string("Socket: ") + strerror(errno));
	}
	struct sockaddr_in adr;
	memset(&adr, 0, sizeof adr);
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	if (bind(_server, (struct sockaddr *)&adr, sizeof adr) == -1){
		throw runtime_error(string("Bind: ") + strerror(errno));
	}
	if (listen(_server, 5) == -1) {
		throw runtime_error(string("Listen: ") + strerror(errno));
	}
}

void Server::run(){
	struct sockaddr_in adr;
	memset(&adr, 0, sizeof adr);
	socklen_t adrlen = sizeof adr;
	int fd = accept(_server, (struct sockaddr *)&adr, &adrlen);
	if (fd == -1) {
		throw runtime_error(string("Accept: ") + strerror(errno));
	}
	ssize_t nread;
	char buf[BUFFER_SIZE];
	nread = recv(fd, buf, BUFFER_SIZE, MSG_NOSIGNAL);
	if (nread == -1) {
		throw runtime_error(string("Recv: ") + strerror(errno));
	} else if (nread == 0) {
		
	}
	cout << buf << endl;
}

Server::~Server() {};
