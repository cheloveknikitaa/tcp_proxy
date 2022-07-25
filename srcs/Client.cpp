#include "Client.hpp"

Client::Client(int fd, Server &server) : _fd(fd), _server(server) {
	Pipe(_toUser);
	Pipe(_fromUser);
	this->_byteTo = 0;
	this->_byteFrom = 0;
}

Client::~Client() {
	if (_byteTo) {
		cout << "SEND TO\n";
		Send(_fd, _byteTo, _toUser[0]);
	}
	(void)_server;
	close(_fd);
	close(_toUser[0]);
	close(_toUser[1]);
	close(_fromUser[0]);
	close(_fromUser[1]);
}

void Client::recv_send(fd_set &rfds){
	if (FD_ISSET(_fd, &rfds)) {
		Recv(_fd, _byteFrom, _fromUser[1]);
	}
	// request_handler
	if (_byteTo) {
		cout << "SEND TO\n";
		Send(_fd, _byteTo, _toUser[0]);
	}
}
