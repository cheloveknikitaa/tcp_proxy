// #include "../../include/parser/Utils.hpp"
#include "../../include/parser/Parser.hpp"


void Serv::initDirectiveListen(vector<string>::iterator &ptr) {
    ListenPort listen;

    //std::cout << "Listen: " << *ptr << std::endl;
    parseListenPath(*ptr, listen);
    ptr++;
    if ((ptr).operator*().compare(";")) {
        listen._isDefault = true;
        ptr++;
    }
    this->_listenPort = listen;

}

void Serv::initDirectiveIndex(vector<string>::iterator &ptr) {

    vector<string> index;

    while ((*ptr).compare(";")) {
        index.push_back(*ptr);
        ptr++;
    }

    this->_index = index;

}

void Serv::initDirectiveRoot(vector<string>::iterator &ptr) {
    this->_root = *ptr;
    ptr++;
}

void Serv::initDirectiveMaxBodySize(vector<string>::iterator &ptr) {
    size_t pos;
    //std::cout << *ptr << std::endl;
    this->_clientMaxBodySize = stoul(*ptr, &pos);
    if (pos < (*ptr).size())
        throw "Invalid syntax file: error format arg";
    ptr++;
}


void Serv::initDirectiveErrorPage(vector<string>::iterator &ptr) {
    //std::cout << *ptr << std::endl;
    size_t pos;
    this->_errorPage.code = stoul(*ptr, &pos);
    if (pos < (*ptr).size())
        throw "Invalid syntax file: error format arg";
    ptr++;
    this->_errorPage.path = *ptr;
    ptr++;
}

void Serv::initDirectiveServerName(vector<string>::iterator &ptr) {
    vector<string> serverNames;

    while ((*ptr).compare(";")) {
        serverNames.push_back(*ptr);
        ptr++;
    }

    this->_serverName = serverNames;
}

void Serv::initDirectiveCgiExtension(vector<string>::iterator &ptr) {

}

void Serv::initDirectiveCgiPath(vector<string>::iterator &ptr) {

}

void Serv::initDirectiveReturn(vector<string>::iterator &ptr) {
    //std::cout << *ptr << std::endl;
    size_t pos;
    this->_return.code = stoul(*ptr, &pos);
    if (pos < (*ptr).size())
        throw "Invalid syntax file: error format arg";
    ptr++;
    this->_return.path = *ptr;
    ptr++;
}

void Serv::initLocation(vector<string>::iterator &ptr) {
    ptr++;
    this->_locations.push_back(Location(*(ptr)));
    // unsigned int countLocation = this->_locations.size() - 1;

    // if (checkCountArgs(path) > 1)
    // 	throw "Error count path";
    // this->_locations.at(countLocation)._path = path;

};


void Serv::initDirective(vector<string>::iterator &ptr) {
    //std::cout << *ptr << std::endl;
    if (!(*ptr).compare("listen"))
        initDirectiveListen(++ptr);
    else if (!(*ptr).compare("root"))
        initDirectiveRoot(++ptr);
    else if (!(*ptr).compare("client_max_body_size"))
        initDirectiveMaxBodySize(++ptr);
    else if (!(*ptr).compare("error_page"))
        initDirectiveErrorPage(++ptr);
    else if (!(*ptr).compare("server_name"))
        initDirectiveServerName(++ptr);
    else if (!(*ptr).compare("cgi_extension"))
        initDirectiveCgiExtension(++ptr);
    else if (!(*ptr).compare("cgi_path"))
        initDirectiveCgiPath(++ptr);
    else if (!(*ptr).compare("return"))
        initDirectiveReturn(++ptr);
    else if (!(*ptr).compare("index"))
        initDirectiveIndex(++ptr);
    else
        throw "Error name command";

}
