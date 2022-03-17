#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

class Client {
private:
    Client();
    int const _UserFd;

    string _response;
    string _IncomingBuffer;
public:
    Client(int const UserFd);
    ~Client();
	string getReplyMessage();
	void updateReplyMessage(string tmp);
	string& getIncomingBuffer();
	int getFd();
};
