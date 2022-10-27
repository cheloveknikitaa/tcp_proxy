#include "include/Request.hpp"

Request::Request(/* args */)
{
}

Request::~Request()
{
}

void	Request::parseRequest(string request)
{
	vector<string> tmp = split(request, "\r\n\r\n");
	vector<string> headers;
	vector<string> tmpHeader;
	if (tmp.size() == 2)
		this->_body = tmp[1];
	headers = split(request, "\n");
	try {
		tmpHeader = split(headers[0], " ");
		if (tmpHeader[0] == "GET")
			this->_method = GET;
		else if (tmpHeader[0] == "POST")
			this->_method = POST;
		else if (tmpHeader[0] == "DELETE")
			this->_method = DELETE;
		this->_path = tmpHeader[1];
		for (size_t i = 1; i < headers.size(); i++)
		{
			tmpHeader = split(headers[i], ":");
			this->_headers.insert(std::pair<string,string>(tmpHeader[0], tmpHeader[1]));
		}
		
	}
	catch (char const *e){
		cout << "Error parse request"<< std::endl;
	}
	
}

std::string	Request::getHeaderValue(string key)
{
	return this->_headers.at(key);
}

std::string	Request::getPath()
{
	return this->_path;
}

eHTTPMethod	Request::getMethod()
{
	return this->_method;
}
