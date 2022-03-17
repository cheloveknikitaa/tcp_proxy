#include "Server.hpp"

Server::Server(char *port): _FdsSet()
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
    while (1) {
        //GetConnectionPart
        int const UserFd = accept(_Sockfd, _ServInfo->ai_addr, &_Socklen);
        if (UserFd >= 0) {
            if (UserFd > _MaxFd) {
                _MaxFd = UserFd;
            }
            fcntl(UserFd, F_SETFD, O_NONBLOCK);
            FD_SET(UserFd, &_FdsSet);
            sockaddr_in AddrUser = {0, 0, 0, {0}, {0}};
            socklen_t Socklen = sizeof(AddrUser);
            getpeername(UserFd, (sockaddr *) &AddrUser, &Socklen);
            std::cout << "+====================CONNECTED======================+" << std::endl;
            std::cout << "<<<<<<< " << inet_ntoa(AddrUser.sin_addr) << std::endl;
            std::cout << "+===================================================+" << std::endl;
			_Clients.push_back(new Client(UserFd));
        }
        send_client();
        reader_client();
    }
}

void Server::send_client(){
	for (vector<Client *>::iterator User = _Clients.begin(); User != _Clients.end(); ++User) {
		std::string ReplyMessage = (*User)->getReplyMessage();
		if (not ReplyMessage.empty()) {
			// std::cout << "+=======================out=========================+" << std::endl;
			// std::cout << ReplyMessage;
			// std::cout << "+===================================================+" << std::endl;
			send((*User)->getFd(), ReplyMessage.c_str(), ReplyMessage.length(), MSG_NOSIGNAL);
		}
		if ((*User)->need_disconected){
			FD_CLR((*User)->getFd(), &_FdsSet);
			delete (*User);
			User = _Clients.erase(User);
		}
		if (User == _Clients.end())
			break;
	}
}

void Server::reader_client(){
	timeval tm = {0, 1000};
	fd_set fdsCopy = _FdsSet;
	if (select(_MaxFd + 1, &fdsCopy, NULL, NULL, &tm) < 0) {
		throw std::runtime_error(std::string("Error: Select") + strerror(errno));
	}
	for (std::vector<Client *>::iterator Client = _Clients.begin();
		 Client != _Clients.end(); ++Client)
	{
		if (FD_ISSET((*Client)->getFd(), &fdsCopy) > 0)
		{
			FD_CLR((*Client)->getFd(), &fdsCopy);
			char Buffer[SIZE] = { 0 };
			ssize_t ReadByte = 0;
			ReadByte = recv((*Client)->getFd(), Buffer, SIZE - 1, 0);
			if (ReadByte < 0) {
				continue ;
			}
			if (ReadByte == 0) {
				// .
			} else {
				(*Client)->getIncomingBuffer() += Buffer;
				// std::cout << "+=======================in==========================+" << std::endl;
				// std::cout << (*Client)->getIncomingBuffer();
				// std::cout << "+===================================================+" << std::endl;
				processCmd(*Client);
			}
		}
	}
}

void Server::processCmd(Client *Client)
{
	if (Client->getIncomingBuffer().end()[-1] != '\n') {
		return ;
	}
	if (!Client->registred){
		Client->connection();
		return;
	}
	query(Client);
}

void Server::query(Client *Client){
	T_RESULT* result;
	try {
		result = Client->getConnection().Query(Client->getIncomingBuffer());
	} catch (const char *e) {
		_response += e;
		_response += "\n"
	}
	
}
