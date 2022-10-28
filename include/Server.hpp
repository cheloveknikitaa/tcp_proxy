#pragma once

#include "Utils.hpp"
#include "Location.hpp"

using namespace std;

class Server {
private:
    int _socket;
    string _index;
    vector<Location_t> _locations;
    string _root;
    string _server_name;
    map<string, string> _error_page;
    string _ip;
    int _port;

    void setLocation(std::vector<string>::iterator &it);

    void setIp(std::vector<string>::iterator &it);

    void setPort(std::vector<string>::iterator &it);

    void setServerName(std::vector<string>::iterator &it);

    void setErrorPage(std::vector<string>::iterator &it);

    void setIndex(std::vector<string>::iterator &it);
public:
    void add_locations(Location &);

    Location &find_locations(string &);

    int get_socket();

    Server(vector<std::string>::iterator &);

    Server(vector<Location_t> locations, string root = "", int port = 80, string server_name = "");

    ~Server();
};
