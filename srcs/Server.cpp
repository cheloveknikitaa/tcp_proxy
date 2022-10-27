#include "Server.hpp"

Server::Server(vector<Location_t> locations, string root, int port, string server_name) : _root(root),
                                                                                          _server_name(server_name),
                                                                                          _port(port) {
    _locations = locations;
    _socket = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr;
    init_adr(adr, port);
    Bind(_socket, (struct sockaddr *) &adr, sizeof adr);
    Listen(_socket, 5);
    Fcntl(_socket);
}

int Server::get_socket() { return (_socket); }


Server::~Server() {
    close(_socket);
}
