#pragma once

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Server {
private:
    bool _LoopListen;
    int _Sockfd;
    addrinfo *_ServInfo;
    socklen_t _Socklen;
    fd_set _FdsSet;
    int _MaxFd;
    Server();
public:
    Server(char *port);
    ~Server();

    void run();
};
