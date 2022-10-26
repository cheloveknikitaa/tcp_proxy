#pragma once
//#include "Serv.hpp"
//#include "../Utils.hpp"

class Serv;

class Location : public Serv {
	public: 
	string	_path;
	// Cgi		_cgi;

	Location (string path = string()) : Serv(), _path(path) {};
	void	initDirective(vector<string>::iterator & ptr);
	void	initDirectiveLimitExcept(vector<string>::iterator & ptr);
	~Location () {};

	// в location не будет server name и listen - обработать, чтобы были недоступны эти методы

};