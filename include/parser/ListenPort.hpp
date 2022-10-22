#pragma once

//#include "../Utils.hpp"

class ListenPort {
	//может в pair отдавать?
	public:
	string _address;
	unsigned long _port;
	bool	_isDefault;
	ListenPort (string address = "0.0.0.0", unsigned long port = 80, bool isDefault = false) : 
		_address(address), _port(port), _isDefault(isDefault) {};

	ListenPort(const ListenPort & other) : _address(other._address), _port(other._port), _isDefault(other._isDefault) {};

	ListenPort & operator=(ListenPort other)
	{
		if (this == &other)
			return (*this);
		_address = other._address;
		_port = other._port;
		_isDefault = other._isDefault;
		return (*this);
	};

};

bool operator== (const pair<int, ListenPort> &f1, const pair<int, ListenPort> &f2);
