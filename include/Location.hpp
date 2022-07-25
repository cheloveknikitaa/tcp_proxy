#pragma once

#include "Utils.hpp"

using namespace std;

#define GET 1<<0
#define POST 1<<1
#define DELETE 1<<2
#define CGI 1<<3

typedef struct Location {
	string _location;
	string _root;
	char _flags;
	string _index;
	Location(string location, string root, string index = "index.html", char flags = GET | POST) : _location(location), _root(root), _index(index) {
		_flags = flags;
	}
}				Location_t;

