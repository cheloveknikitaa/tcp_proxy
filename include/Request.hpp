#include "Utils.hpp"

typedef enum{
	GET,
	POST,
	DELETE
} eHTTPMethod;

class Request
{
private:
	eHTTPMethod _method;
	string _path;
	//string protocol;
	map <string, string > _headers;
	string _body;
public:
	Request(/* args */);
	~Request();
	void	parseRequest(string request);
	string	getHeaderValue(string key);
	string	getPath();
	eHTTPMethod	getMethod();
};
