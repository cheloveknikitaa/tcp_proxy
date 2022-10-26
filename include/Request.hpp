#include "Utils.hpp"

typedef enum{
	GET,
	POST,
	DELETE
} eHTTPMethod;

class Request
{
private:
	eHTTPMethod method;
	string path;
	map <string, vector<string> > headers;
public:
	Request(/* args */);
	~Request();
	void	initRequest();
};

Request::Request(/* args */)
{
}

Request::~Request()
{
}
