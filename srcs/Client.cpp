#include "Client.hpp"

Client::Client(int fd): _portDb(-1) {
	_db = Socket(AF_INET, SOCK_STREAM, 0);
	_fd = fd;
	_registred = false;
	Pipe(_toUser);
	Pipe(_fromUser);
	write(_toUser[1], "ip: ", 4);
	_byteTo = 4;
}

Client::Client(int fd, string ip, int port) : _portDb(port), _ipDb(ip) {
	_db = Socket(AF_INET, SOCK_STREAM, 0);
	_fd = fd;
	ConnectToDB();
	Pipe(_toUser);
	Pipe(_fromUser);
}

Client::~Client() {
	close(_db);
	close(_fd);
	close(_toUser[0]);
	close(_toUser[1]);
	close(_fromUser[0]);
	close(_fromUser[1]);
}

int Client::getDb() { return _db; }

void Client::connection(fd_set &_FdsSet){
	char buf[BUFFER_SIZE] = { 0 };
	ssize_t nread = read(_fromUser[0], buf, _byteFrom);
	_byteFrom -= nread;
	string query = buf;

	query.erase(query.end() - 1);
	if (_ipDb.empty() ) {
		_ipDb = query;
		write(_toUser[1], "port: ", 6);
		_byteTo = 6;
	} else if ( _portDb == -1 ) {
		_portDb = stoi(query);
		try {
			ConnectToDB();
			FD_SET(_db, &_FdsSet);
		} catch (std::exception &e) {
			send(_fd, e.what(), strlen(e.what()), MSG_NOSIGNAL);
			throw _fd;
		}
	}
}

void Client::recv_send(fd_set &rfds, fd_set &_FdsSet){
	if (FD_ISSET(_fd, &rfds)){
		Recv(_fd, _byteFrom, _fromUser[1]);
		if (!_registred) {
			connection(_FdsSet);
		}
	}
	if (FD_ISSET(_db, &rfds)){
		Recv(_db, _byteTo, _toUser[1]);
	}
	if (_byteTo){
		cout << "SEND TO\n";
		Send(_fd, _byteTo, _toUser[0]);
	}
	if (_byteFrom){
		cout << "SEND FROM\n";
		Send(_db, _byteFrom, _fromUser[0]);
	}
}

void Client::ConnectToDB(){
	struct sockaddr_in adr;
	cout << _ipDb << ":" << _portDb << "\n";
	init_adr(adr, _portDb);
	Inet_aton(_ipDb.c_str(), adr.sin_addr);
	Connect(_db, (struct sockaddr *)&adr, sizeof adr);
	Fcntl(_db);
	_registred = true;
}
