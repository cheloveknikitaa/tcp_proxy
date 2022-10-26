#pragma once
// #include "../Utils.hpp"
#include "ListenPort.hpp"
//#include "Location.hpp"

struct Cgi {

};

struct ErrorPage {
	unsigned long code;
	string path;
};

struct Return {
	unsigned long code;
	string path;
};

class Location;

class Serv
{

	public:
	ListenPort _listenPort;
	vector <string> _serverName;
	vector <Location> _locations;
	ErrorPage _errorPage;
	Return	_return;
	unsigned long _clientMaxBodySize;
	vector <string>	_method;
	vector <string>	_index;
	string _root;
	Serv(void) {
		//какое то значение по умолчанию
		_clientMaxBodySize = 0;
		//если по умолчанию все методы
		_method.push_back("GET");
		_method.push_back("POST");
		_method.push_back("DELETE");
		_return.code = 0;
		_errorPage.code = 0;
		//_index.push_back("index.html");
		//_listenPort();
		
	};
	public:
	//переобределить в Location - сделать недоступной
	void	initLocation(vector<string>::iterator & ptr);
	void	initDirective(vector<string>::iterator & ptr);
	void	initDirectiveListen(vector<string>::iterator & ptr);
	void	initDirectiveReturn(vector<string>::iterator & ptr);
	void	initDirectiveCgiPath(vector<string>::iterator & ptr);
	void	initDirectiveCgiExtension(vector<string>::iterator & ptr);
	void	initDirectiveServerName(vector<string>::iterator & ptr);
	void	initDirectiveErrorPage(vector<string>::iterator & ptr);
	void	initDirectiveMaxBodySize(vector<string>::iterator & ptr);
	void	initDirectiveRoot(vector<string>::iterator & ptr);
	void	initDirectiveIndex(vector<string>::iterator & ptr);


};
