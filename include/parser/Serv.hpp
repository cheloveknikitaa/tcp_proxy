#pragma once
// #include "../Utils.hpp"
#include "ListenPort.hpp"
//#include "Location.hpp"

struct Cgi {

};

struct ErrorPage {
	unsigned int code;
	string path;
};

struct Return {
	unsigned int code;
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
		//_listenPort();
		
	};
	public:
	//переобределить в Location - сделать недоступной
	void	initLocation(string &line);
	void	initDirective(string &line, string &command);
	void	processingCommandListen(string &line);
	void	processingReturn(string &line);
	void	processingCgiPath(string &line);
	void	processingCgiExtension(string &line);
	void	processingServerName(string &line);
	void	processingErrorPage(string &line);
	void	processingLimitExcept(string &line);
	void	processingCommandMaxBodySize(string &line);
	void	processingCommandRoot(string &line);


};
