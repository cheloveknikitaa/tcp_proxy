#include "Server.hpp"

Server::Server(char *port):
        _LoopListen(true),
        _Sockfd(-1),
        _ServInfo(NULL),
        _Socklen(0),
        _FdsSet(),
        _MaxFd(0)
{
    addrinfo hints;
    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, port, &hints, &_ServInfo))
        throw std::runtime_error(
                string("getaddrinfo error: ") + gai_strerror(errno));
    _Sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_Sockfd < 0)
        throw std::runtime_error(string("Socket: ") + strerror(errno));
    if (fcntl(_Sockfd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error(string("fcntl: ") + strerror(errno));
    _Socklen = sizeof(sockaddr);
    if (bind(_Sockfd, _ServInfo->ai_addr, _Socklen))
        throw std::runtime_error(string("bind: ") + strerror(errno));
    if (listen(_Sockfd, SOMAXCONN))
        throw std::runtime_error(string("listen: ") + strerror(errno));
}

Server::~Server(){
    freeaddrinfo(_ServInfo);
    close(_Sockfd);
}

void Server::run() {
    std::cout << "Waiting for a connection..." << '\n';
    while (_LoopListen) {
        //GetConnectionPart
        int const UserFd = accept(_Sockfd, _ServInfo->ai_addr, &_Socklen);
        if (UserFd >= 0) {
            if (UserFd > _MaxFd) {
                _MaxFd = UserFd;
            }
            fcntl(UserFd, F_SETFD, O_NONBLOCK);
            FD_SET(UserFd, &_FdsSet);
#ifdef __linux__
            sockaddr_in AddrUser = {0,0,{0},{0}};
#elif __APPLE__
            sockaddr_in AddrUser = {0, 0, 0, {0}, {0}};
#endif
            socklen_t Socklen = sizeof(AddrUser);
            getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen);
            std::cout << "+====================CONNECTED======================+" << std::endl;
            std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr) << std::endl;
            std::cout << "+===================================================+" << std::endl;
        }

    }
}
