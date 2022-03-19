#include "Client.hpp"

Client::Client(int fd) {
	_db = Socket(AF_INET, SOCK_STREAM, 0);
	_fd = fd;
	_registred = false;
	Memcpy(_bufferToClient, "ip: ", 4, _byteTo);
}

Client::~Client() {
	close(_db);
	close(_fd);
}

int Client::getDb() { return _db; }

void Client::connection(fd_set &_FdsSet){
	string query = _bufferFromClient;

	query.erase(query.end() - 1);
	if (_ipDb.empty() ) {
		_ipDb = query;
		Memcpy(_bufferToClient, "port: ", 6 , _byteTo);
	} else if (_portDb.empty() ) {
		_portDb = query;
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
		Recv(_fd, _byteFrom, _bufferFromClient);
		cout << _bufferFromClient;
		if (!_registred) {
			connection(_FdsSet);
		}
	}
	if (FD_ISSET(_db, &rfds)){
		Recv(_db, _byteTo, _bufferToClient);
	}
	if (_byteTo){
		Send(_fd, _bufferToClient, _byteTo);
	}
	if (_byteFrom){
		if (containsSql(_bufferFromClient))
			createLog(_bufferFromClient, _ipDb, _portDb);
		Send(_db, _bufferFromClient, _byteFrom);
	}
}

void Client::ConnectToDB(){
	struct sockaddr_in adr;
	init_adr(adr, stoi(_portDb));
	Inet_aton(_ipDb.c_str(), adr.sin_addr);
	Connect(_db, (struct sockaddr *)&adr, sizeof adr);
	Fcntl(_db);
	_registred = true;
}
