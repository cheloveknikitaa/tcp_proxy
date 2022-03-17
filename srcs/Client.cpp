#include "Client.hpp"

Client::Client(int const UserFd): _UserFd(UserFd) {
	_response += "host: ";
}

void Client::connection(){
	string query = _IncomingBuffer;
	query.end()[-1] = '\0';
	if (_host.empty() ) {
		_host = query;
		_response += "port: ";
	} else if (_port.empty() ){
		_port = query;
		_response += "user: ";
	} else if (_user.empty() ) {
		_user = query;
		_response += "pass: ";
	} else if (_pass.empty() ) {
		_pass = query;
		_response += "db: ";
	} else if (_db.empty() ) {
		MYSQL mysql;
		_db = query;
		registred = true;
		mysql_init(&mysql);
		std::cout << "\n\nhost: " << _host << "\nuser: " << _user << "\npass: " << _pass << "\ndb: " << _db << "\nport: " << _port << "\n";
		_connection = mysql_real_connect(&mysql, _host.c_str(), _user.c_str(), _pass.c_str(), _db.c_str(), stoi(_port), 0, 0);
		if (_connection == NULL)
		{
			std::cout <<  mysql_error(&mysql) << "\n";
			_response += mysql_error(&mysql);
			_response += "\nbye!\n";
			need_disconected = true;
			return ;
		}
		_response += "connected!\nquery: ";
	}
	_IncomingBuffer.clear();
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
