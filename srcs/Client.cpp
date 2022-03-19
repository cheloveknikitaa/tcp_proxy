#include "Client.hpp"

Client::Client(int fd) {
	_db = Socket(AF_INET, SOCK_STREAM, 0);
	_fd = fd;
	_registred = false;
	_bufferToClient = "ip: ";
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
		_bufferToClient = "port: ";
	} else if (_portDb.empty() ) {
		_portDb = query;
		try {
			ConnectToDB();
			FD_SET(_db, &_FdsSet);
		} catch (std::exception &e) {
			Send(_fd, e.what());
			throw _fd;
		}
	}
}

void Client::recv_send(fd_set &rfds, fd_set &_FdsSet){
	if (FD_ISSET(_fd, &rfds)){
		_bufferFromClient += Recv(_fd);
		cout << _bufferFromClient;
		if (_bufferFromClient.end()[-1] == '\n') {
			if (!_registred) {
				connection(_FdsSet);
				_bufferFromClient.clear();
			}
		}
	}
	if (FD_ISSET(_db, &rfds)){
		_bufferToClient += Recv(_db);
	}
	if (!_bufferToClient.empty()){
		Send(_fd, _bufferToClient);
		_bufferToClient.clear();
	}
	if (!_bufferFromClient.empty() && _bufferFromClient.end()[-1] == '\n'){
		if (containsSql(_bufferFromClient))
			createLog(_bufferFromClient, _ipDb, _portDb);
		Send(_db, _bufferFromClient);
		_bufferFromClient.clear();
	}
}

void Client::ConnectToDB(){
	struct sockaddr_in adr;
	init_adr(adr, stoi(_portDb));
	Inet_pton(AF_INET, _ipDb.c_str(), &adr.sin_addr);
	Connect(_db, (struct sockaddr *)&adr, sizeof adr);
	Fcntl(_db);
	_registred = true;
}
