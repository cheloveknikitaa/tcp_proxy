// #include "../../include/parser/Utils.hpp"
#include "../../include/parser/Parser.hpp"

void checkAddress(string &address) {
    string::iterator it;
    vector<unsigned int> count(1);


    for (it = address.begin(); it != address.end(); it++) {
        // server_name == имени хоста?
        if (!isalpha(*it))
            break;
    }
    if (it == address.end())
        return;
    for (it = address.begin(); it != address.end(); it++) {

        if (*it == '.') {
            if (count.at(count.size() - 1) > 0 && count.at(count.size() - 1) < 4) {
                count.push_back(0);
                continue;
            } else
                throw "Invalid value address";
        }
        count.at(count.size() - 1)++;
    }
    if (count.size() != 4)
        throw "Invalid value address";
}

void parseListenPath(string &path, ListenPort &listen) {
    //validation ip - Inet_aton
    string::iterator it;
    string::iterator ite;
    size_t pos;
    string address;
    address = path;
    ite = address.begin();

    //without ipv6
    // Обрабатываемые кейсы:
    // listen 127.0.0.1:8000;
    // listen 127.0.0.1;
    // listen 8000;
    // listen *:8000;
    // listen localhost:8000;

    for (it = path.begin(); it != path.end(); it++) {
        if (*it == ':')
            break;
        ite++;
    }
    if (it == path.end()) {
        for (it = path.begin(); it != path.end(); it++) {
            if (isalpha(*it) || *it == '.')
                break;
        }
        if (it != path.end()) {
            checkAddress(path);
            listen._address = path;
            listen._port = "80";
        } else {
            listen._port = path;
            //std::cout << listen._port << std::endl;
            if (pos < path.size())
                throw "Invalid value port";
            listen._address = "0.0.0.0";
        }
    } else {
        if (*it == ':' && *(path.begin()) == '*')
            listen._address = "0.0.0.0";
        else {
            address.erase(ite, address.end());
            checkAddress(address);
            listen._address = address;
            path.erase(path.begin(), it.operator++());
            listen._port = path;
            if (pos < path.size())
                throw "Invalid value port";
        }
    }

}

