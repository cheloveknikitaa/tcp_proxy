#pragma once

#include "../Utils.hpp"
#include "Serv.hpp"
#include "Utils.hpp"
#include "Location.hpp"

class Parser {
private:
    vector<Serv> _servers;
    pair<bool, string> _context;
    vector<std::string> conf;

    void eraseComment(string &line);

    void checkDefaultServers();

    void initData();

    void fillServers();

    void showData();

    void checkEndDirective(vector<string>::iterator &ptr);

    void validationConfig(string &line);

    void split(string &line);

    void validationCloseContext(vector<string>::iterator &ptr);

    void validationOpenContext(vector<string>::iterator &ptr);

    void validationServer(vector<string>::iterator &ptr);

    void validationLocation(vector<string>::iterator &ptr);

    void validationContextDirective(vector<string>::iterator &ptr);

    void validationDirective(vector<string>::iterator &ptr);

    void validationDirectiveListen(vector<string>::iterator &ptr);

    void validationDirectiveReturn(vector<string>::iterator &ptr);

    void validationDirectiveCgiPath(vector<string>::iterator &ptr);

    void validationDirectiveCgiExtension(vector<string>::iterator &ptr);

    void validationDirectiveServerName(vector<string>::iterator &ptr);

    void validationDirectiveErrorPage(vector<string>::iterator &ptr);

    void validationDirectiveLimitExcept(vector<string>::iterator &ptr);

    void validationDirectiveMaxBodySize(vector<string>::iterator &ptr);

    void validationDirectiveRoot(vector<string>::iterator &ptr);

    void validationDirectiveIndex(vector<string>::iterator &ptr);

public:
    Parser(void) : _context(false, std::string()) { };

    void parse(const std::string &filename);

    vector<std::string> &getConf() { return conf; }

    ~Parser() { };
};
