#pragma once

#include </usr/include/mysql/mysql.h> // Заголовочный файл с описание функций
#include <stdio.h>
// #include <conio.h>
#include <string>
#include <iostream>
#include <unistd.h>

#include "Connection.hpp"

// #include <cppconn/driver.h>
// #include <cppconn/exception.h>
// #include <cppconn/resultset.h>
// #include <cppconn/statement.h>

using namespace std;

class Client {
private:
    Client();
    int const _UserFd;
    string _host;
    string _port;
    string _user;
    string _pass;
    string _db;
    string _response;
    string _IncomingBuffer;
    Connection _connection;
public:
    bool need_disconected;
	bool registred { false };
    Client(int const UserFd);
    ~Client();
	string getReplyMessage();
	void updateReplyMessage(string tmp);
	string& getIncomingBuffer();

	MYSQL *getDbFd();
	int getFd();
};
