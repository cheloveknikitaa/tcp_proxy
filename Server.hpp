#pragma once

class Server : public Modes {
private:
    std::string const _Name;

    // Parameters
    std::string _Ip;
    std::string _Port;

    // Networking
    bool _LoopListen;
    int _Sockfd;
    addrinfo *_ServInfo;
    socklen_t _Socklen;
    fd_set _FdsSet;
    int _MaxFd;

    // Top level logic
    std::set<Client *> _Clients;
    std::list<Client *> _ClientsToBeErased;

    // Insights
    void readerClients();
    void replyToClients();
    void processCmd(Client *User);
    std::pair<std::string, std::string> parseCmd(std::string &Cmd);
    void proceedCmd(std::pair<std::string, std::string> Cmd, Client *User);
    void serverLog(Client *that, std::string const & ReceivedMessage);

public:
    Server(string const & Port);
    ~Server();

    void run();
    std::string getServerAddrInfo() const { return _Ip + ":" + _Port; }
    bool pushBack(Channel *Channel);
    void pushBackErase(Client *Client);
    void buryMe(std::string const & DyingMessage);
};

Server::Server(string const & Port)
        :   Modes(),
            _Name(SERVER_NAME),
            _Ip("0"),
            _Port(Port),
            _LoopListen(true),
            _Sockfd(-1),
            _ServInfo(NULL),
            _Socklen(0),
            _FdsSet(),
            _MaxFd(0){
    addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(_Ip.c_str(), _Port.c_str(), &hints, &_ServInfo))
        throw std::runtime_error(
                string("getaddrinfo error: ") + gai_strerror(errno));
    if (1024 > std::atoi(_Port.c_str()) || std::atoi(_Port.c_str()) > 49151)
        throw std::runtime_error("wrong _Port! min 1024, max 49151,");
    std::cout << "Server will be bound to _Port: " << _Port << '\n';
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

void Server::buryMe(std::string const & DyingMessage) {
    _DyingMessage = DyingMessage + "\r\n";
    _LoopListen = false;
}

Server::~Server(void)
{
    freeaddrinfo(_ServInfo);
    close(_Sockfd);
}

void Server::run()
{
    std::cout << "Waiting for a connection..." << '\n';
    while (_LoopListen)
    {
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
            sockaddr_in AddrUser = {0,0,0,{0},{0}};
#endif
            socklen_t Socklen = sizeof(AddrUser);
            getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen);
            std::cout << "+====================CONNECTED======================+" << '\n';
            std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr) << '\n';
            std::cout << "+===================================================+" << std::endl;
            _Clients.insert(new Client(UserFd, inet_ntoa(AddrUser.sin_addr)));
        }

        //ReadPart
        readerClients();

        //Reply part
        replyToClients();

        //Erase dead clients
        eraseClientsAndChannels();
    }
}

void Server::readerClients()
{
    timeval tm = {0, 1000};
    fd_set fdsCopy = _FdsSet;
    if (select(_MaxFd + 1, &fdsCopy, NULL, NULL, &tm) < 0) {
        throw std::runtime_error(std::string("Error: Select") + strerror(errno));
    }
    for (std::set<Client *>::iterator Client = _Clients.begin();
         Client not_eq _Clients.end(); ++Client)
    {
        if (FD_ISSET((*Client)->_Fd, &fdsCopy) > 0)
        {
            FD_CLR((*Client)->_Fd, &fdsCopy);
            char Buffer[SIZE] = { 0 };
            ssize_t ReadByte = 0;
            ReadByte = recv((*Client)->_Fd, Buffer, SIZE - 1, 0);
            if (ReadByte < 0) {
                continue ;
            }
            if (ReadByte == 0) {
                QUIT q(*this);
                q.setQuitInitiator(*Client);
                q.setArgument(std::string(":Is dead. Just dead. People die, ya know?"));
            } else {
                (*Client)->getIncomingBuffer() += Buffer;
                serverLog(*Client, (*Client)->getIncomingBuffer());
                processCmd(*Client);
            }
        }
    }
}

void Server::processCmd(Client *Client)
{
    if (Client->getIncomingBuffer().end()[-1] not_eq '\n') {
        return ;
    }
    if (Client->getIncomingBuffer().find_first_not_of("\r\n") == Client->getIncomingBuffer().npos) {
        Client->getIncomingBuffer().clear();
        return ;
    }
    std::vector<std::string> Cmds = ft::split(Client->getIncomingBuffer(), "\n");
    for (std::vector<std::string>::iterator i = Cmds.begin(); i != Cmds.end(); ++i) {
        ft::deleteSpaces(*i, "\r");
    }
    Client->getIncomingBuffer().clear();
    for (std::vector<std::string>::iterator it = Cmds.begin();
         it not_eq Cmds.end(); ++it) {
        std::pair<std::string, std::string> Cmd = parseCmd(*it);
        proceedCmd(Cmd, Client);
    }
}

void Server::serverLog(Client *That, std::string const & ReceivedMessage)
{
    std::cout << "+========================in========================+" << std::endl;
    std::cout << That->getNickName() << ": "<< ReceivedMessage;
    std::cout << "+==================================================+" << std::endl;
}
