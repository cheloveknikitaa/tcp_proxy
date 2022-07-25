#include "Core.hpp"


void Core::run(){
	std::cout << "Waiting for a connection..." << '\n';
	fd_set rfds;
	while (1) {
		rfds = _FdsSet;
		select(_MaxFd + 1, &rfds, NULL, NULL, NULL);
		for(map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); ++it) {
			if (FD_ISSET((*it).second.get_socket() , &rfds)) {
				newConnection((*it).second);
			}
		}
		for(std::vector<Client *>::iterator it = _Clients.begin();
			it != _Clients.end(); ++it) {
			try {
				(*it)->recv_send(rfds);
			} catch (int fd) {
				cout << "disconected!\n";
				FD_CLR(fd, &_FdsSet);
				delete(*it);
				it = _Clients.erase(it);
			} catch (std::exception &e) { throw e; }
			if (it == _Clients.end())
				break;
		}
	}
}

void Core::newConnection(Server &server){
	int const UserFd = Accept(server.get_socket(), NULL, NULL);
	cout << "Connected! "<< UserFd << "\n";
	if (UserFd >= 0) {
		Client *newClient;
		fcntl(UserFd, F_SETFD, O_NONBLOCK);
		newClient = new Client(UserFd, server);
		_Clients.push_back(newClient);
		FD_SET(UserFd, &_FdsSet);
		_MaxFd = max(_MaxFd, UserFd);
	}
}

Core::Core(string path_to_config)
{
	FD_ZERO(&_FdsSet);
	if (path_to_config == "default") {
		vector<Location_t> locations;
		locations.push_back(Location("/","./html/"));
		Server serv(locations);
		FD_SET(serv.get_socket(), &_FdsSet);
		pair<int, Server> tmp = std::make_pair(80, serv);
		this->_servers.insert(tmp);
	}
	// pars conf
	// _MaxFd = _socket;
	// FD_SET(_socket, &_FdsSet);
}

Core::~Core()
{
	for(std::vector<Client *>::iterator it = _Clients.begin();
		it != _Clients.end(); ++it) {
		delete (*it);
		it = _Clients.erase(it);
		if (it == _Clients.end())
			break;
	}
	//erase servers
}