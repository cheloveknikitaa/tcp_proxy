#pragma once
//#include "Serv.hpp"
//#include "../Utils.hpp"

class Serv;

class Location : public Serv {
	public: 
	string	_path;
	// Cgi		_cgi;

	Location () : Serv() {};
	void	initDirective(string &line, string &command);
	~Location () {};

};
