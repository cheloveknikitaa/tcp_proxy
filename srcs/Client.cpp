#include "Client.hpp"

Client::Client(int fd) {
	_fd = fd;
	Pipe(_toUser);
	Pipe(_fromUser);
}

Client::~Client() {
	close(_fd);
	close(_toUser[0]);
	close(_toUser[1]);
	close(_fromUser[0]);
	close(_fromUser[1]);
}

void Client::recv_send(fd_set &rfds){
	if (FD_ISSET(_fd, &rfds)){
		Recv(_fd, _byteFrom, _fromUser[1]);
	}
	if (_byteTo){
		cout << "SEND TO\n";
		Send(_fd, _byteTo, _toUser[0]);
	}
}
