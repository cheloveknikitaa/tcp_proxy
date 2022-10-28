#pragma once

#include "Utils.hpp"

using namespace std;

#define GET 1<<0
#define POST 1<<1
#define DELETE 1<<2
#define CGI 1<<3

struct Location {
public:
    bool _autoIndex;
	string _root;
	char _flags;
	string _index;
    ssize_t _clientBodySize;
    bool _autoindex;
    int _return;

	Location (vector<std::string>::iterator &it) {
        _flags = 0;
        for (; *it != "}" ; ++it) {
            if (*it == "index") {
                setIndex(++it);
            } else if (*it == "autoindex") {
                setAutoIndex(++it);
            } else if (*it == "root") {
                setRoot(++it);
            } else if (*it == "client_max_body_size") {
                setClientBodySize(++it);
            }
        }
	}
private:

    void setIndex(std::vector<string>::iterator &it){
        _index = (*it);
    }

    void setAutoIndex(std::vector<string>::iterator &it) {
        if (*it == "true")
            _autoIndex = true;
        else if (*it == "false")
            _autoIndex = false;
        else
            throw logic_error("Unexpepted token: " + *it);
        it++;
    }

    void setRoot(std::vector<string>::iterator &it) {
        _root = *it++;
    }

    void setClientBodySize(std::vector<string>::iterator &it) {
        _clientBodySize = stoull(*it++);
    }
};

