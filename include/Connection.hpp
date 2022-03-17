#pragma once
#include <sys/time.h>

#include </usr/include/mysql/mysql.h>

#include "Result.hpp"

class Connection
{
public:
	Connection(const char*,const char*);
	Connection(const char*,const char*,const char*,const char*);
	~Connection();

	void Close();
	void Connect(const char* host,const char* dataBase,
					const char* userID,const char* password);
	int GetAffectedRows() const;
	const char* GetError();
	int IsConnected() const;
	Result* Query(const char* sqlCommand);

	private:
	int affectedRows;
	MYSQL mysql;
	MYSQL* connection;
};
