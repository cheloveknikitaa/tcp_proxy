#include "Server.hpp"

int Server::get_socket() { return (_socket); }

Server::Server(vector<std::string>::iterator &it) {
    for (; *it != "}" ; ++it) {
        // if (*it == "location") {
        //     _locations[*++it] = Location(++it);
        if (*it == "ip") {
            setIp(++it);
        }  else if (*it == "port") {
            setPort(++it);
        } else if (*it == "server_name") {
            setServerName(++it);
        } else if (*it == "error_page") {
            setErrorPage(++it);
        } else if (*it == "index") {
            setIndex(++it);
        } else if (*it == "autoindex") {
            setAutoIndex(++it);
        } else if (*it == "root") {
            setRoot(++it);
        } else if (*it == "client_max_body_size") {
            setClientBodySize(++it);
        }
        _socket = Socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in adr;
        adr.sin_addr.s_addr = inet_addr(_ip.c_str());
        init_adr(adr, _port);
        Bind(_socket, (struct sockaddr *) &adr, sizeof adr);
        Listen(_socket, 5);
        Fcntl(_socket);
    }
}

Server::~Server() {
    close(_socket);
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

void Server::setAutoIndex(std::vector<string>::iterator &it) {
    if (*it == "true")
        _autoIndex = true;
    else if (*it == "false")
        _autoIndex = false;
    else
        throw logic_error("Unexpepted token: " + *it);
    it++;
}

void Server::setRoot(std::vector<string>::iterator &it) {
    _root = *it++;
}

void Server::setClientBodySize(std::vector<string>::iterator &it) {
    _clientBodySize = stoull(*it++);
}


