// // #include "../../include/parser/Serv.hpp"
// #include "../../include/parser/Location.hpp"
#include "../../include/parser/Parser.hpp"

void	Location::initDirectiveLimitExcept(vector<string>::iterator & ptr)
{
	vector <string> methods;

	while ((*ptr).compare(";"))
	{
		methods.push_back(*ptr);
		ptr++;
	}
	this->_method = methods;
}

void	Location::initDirective(vector<string>::iterator & ptr)
{
	//std::cout << *ptr << std::endl;
	if (!(*ptr).compare("limit_except"))
		initDirectiveLimitExcept(++ptr);
	else if(!(*ptr).compare("root"))
		initDirectiveRoot(++ptr);
	else if (!(*ptr).compare("client_max_body_size"))
		initDirectiveMaxBodySize(++ptr);
	else if (!(*ptr).compare("error_page"))
		initDirectiveErrorPage(++ptr);
	else if (!(*ptr).compare("cgi_extension"))
		initDirectiveCgiExtension(++ptr);
	else if (!(*ptr).compare("cgi_path"))
		initDirectiveCgiPath(++ptr);
	else if (!(*ptr).compare("return"))
		initDirectiveReturn(++ptr);
	else
		throw "Error name command";

}