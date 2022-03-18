#include "Utils.hpp"

int Socket(int domain, int type, int protocol){
	int res = socket(domain, type, protocol);
	if (res == -1) {
		throw runtime_error(string("Socket: ") + strerror(errno));
	}
	return res;
}

int Bind(int socket, const struct sockaddr *address,
		socklen_t address_len){
	int res = bind(socket, address, address_len);
	if (res == -1) {
		throw runtime_error(string("Bind: ") + strerror(errno));
	}
	return res;
}

int Listen(int socket, int backlog){
	int res = listen(socket, backlog);
	if (res == -1) {
		throw runtime_error(string("Listen: ") + strerror(errno));
	}
	return res;
}

int Accept(int socket, struct sockaddr *address,
		   socklen_t *address_len){
	int res = accept(socket, address, address_len);
	if (res == -1) {
//		throw runtime_error(string("Accept: ") + strerror(errno));
	}
	return res;
}

int Connect(int socket, struct sockaddr *address,
			socklen_t address_len){
    int res = connect(socket, address, address_len);
    if (res == -1) {
        throw runtime_error(string("Connect: ") + strerror(errno));
    }
    return res;
}

int Inet_pton(int af, const char *src, void *dst){
	int res = inet_pton(af, src, dst);
	if (res == -1) {
		throw runtime_error(string("Inet_pton: ") + strerror(errno));
	} else if (res == 0) {
		throw runtime_error(string("Inet_pton: the address was not parseable in the specified address family"));
	}
    return res;
}

void init_adr(struct sockaddr_in &adr, int port){
	memset(&adr, 0, sizeof adr);
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
}

void Fcntl(int fd){
	int res = fcntl(fd, F_SETFD, O_NONBLOCK);
	if (res == -1) {
		throw runtime_error(string("fcntl: ") + strerror(errno));
	}
}

string Recv(int fd){
	ssize_t nread;
	char buf[BUFFER_SIZE] = { 0 };
	nread = recv(fd, buf, BUFFER_SIZE - 1, MSG_NOSIGNAL);
	if (nread == -1) {
		throw runtime_error(string("Recv: ") + strerror(errno));
	} else if (nread == 0) {
		throw fd;
	}
	return buf;
}

void Send(int fd, string msg) {
	ssize_t res = send(fd, msg.c_str(), msg.length(), MSG_NOSIGNAL);
	if (res == -1) {
		throw runtime_error(string("Send: ") + strerror(errno));
	}
}


