#pragma once

#include "Utils.hpp"

class Location // struct??
{
private:
	string _root;
	string _cgi;
	set<string> _methods;
	string _index = "index.html";
public:
	Location(/* args */);
	~Location();
};

Location::Location(/* args */)
{
}

Location::~Location()
{
}
