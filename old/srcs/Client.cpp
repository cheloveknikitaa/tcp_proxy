#include "Client.hpp"

Client::Client(int const UserFd): _UserFd(UserFd) {
	_response += "host: ";
}

void Client::connection(){
	
}

string& Client::getIncomingBuffer() {
	return _IncomingBuffer;
}

string Client::getReplyMessage(){
	string res = _response;
	_response.clear();
	return res;
}

MYSQL *Client::getDbFd(){
	return _connection;
}

int Client::getFd(){
	return _UserFd;
}

void Client::updateReplyMessage(string tmp){
	_response += tmp;
}

Client::~Client(){
	close(_UserFd);
	if (_connection)
		mysql_close(_connection);
}

Connection Client::getConnection(){
	return _connection;
}


// _connection = mysql_real_connect(&mysql, _host.c_str(), _user.c_str(), _pass.c_str(), _db.c_str(), stoi(_port), 0, 0);
// std::cout << "\n\nhost: " << _host << "\nuser: " << _user << "\npass: " << _pass << "\ndb: " << _db << "\nport: " << _port << "\n";
//