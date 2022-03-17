#include "Client.hpp"

Client::Client(int fd) {
	_db = Socket(AF_INET, SOCK_STREAM, 0);
	_fd = fd;
}
//
//void Client::ConnectToDB(){
//	struct sockaddr_in adr;
//	init_adr(adr, _portDb);
//	Inet_pton(AF_INET, _ipDb.c_str(), &adr.sin_addr);
//	Connect(_db, (struct sockaddr *)&adr, sizeof adr);
//	Fcntl(_db);
//}
