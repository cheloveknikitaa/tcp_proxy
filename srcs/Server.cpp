#include "Server.hpp"

Server::Server(vector<Location_t> locations, string root, int port, string server_name) : _root(root),
                                                                                          _server_name(server_name),
                                                                                          _port(port) {
    _locations = locations;
    _socket = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr;
    adr.sin_addr.s_addr = inet_addr(_ip.c_str());
    init_adr(adr, port);
    Bind(_socket, (struct sockaddr *) &adr, sizeof adr);
    Listen(_socket, 5);
    Fcntl(_socket);
}

int Server::get_socket() { return (_socket); }


Server::Server(vector<std::string>::iterator &it) {
    for (; *it != "}" ; ++it) {
        if (*it == "location") {
            setLocation(it);
        } else if (*it == "ip") {
            setIp(++it);
        }  else if (*it == "port") {
            setPort(++it);
        } else if (*it == "server_name") {
            setServerName(++it);
        } else if (*it == "error_page") {
            setErrorPage(++it);
        } else if (*it == "index") {
            setIndex(++it);
        }

    }
}


Server::~Server() {
    close(_socket);
}


void Server::setLocation(std::vector<string>::iterator &it){

}

void Server::setIp(std::vector<string>::iterator &it){
    _ip = *it++;
}
void Server::setPort(std::vector<string>::iterator &it){
    _port = stoi(*it++);
}

void Server::setServerName(std::vector<string>::iterator &it){
        _server_name = *it;
}

void Server::setErrorPage(std::vector<string>::iterator &it){
    if ((_error_page.find(*it)) != _error_page.end())
        _error_page[*it++] = *it++;
    else {
        throw logic_error("rewriting error code " + *it);
    }
}

void Server::setIndex(std::vector<string>::iterator &it){
        _index = (*it);
}

