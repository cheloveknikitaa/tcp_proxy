#include "../../include/parser/Parser.hpp"


void	Parser::validationContextDirective(vector<string>::iterator & ptr)
{
	if (this->_context.second.compare("server") && this->_context.second.compare("location"))
		throw "Error context directive";
	if (!this->_context.first)
		throw "Error open context directive";
	if (!this->_context.second.compare("server") && (!(*ptr).compare("limit_except")))
		throw "Error context for limit_except";
	if (!this->_context.second.compare("location") && (!(*ptr).compare("listen")))
		throw "Error context for listen";
}

void	Parser::validationCloseContext(vector<string>::iterator & ptr)
{
	
	if (this->_context.second.empty())
		throw "Error close context";
	if (!this->_context.second.compare("location"))
	{
		this->_context.second = "server";
		this->_context.first = true;
	}
	else if (!this->_context.second.compare("server"))
	{
		this->_context.first = false;
		this->_context.second = string();
	}
}

void	Parser::validationOpenContext(vector<string>::iterator & ptr)
{
	size_t index = this->conf.size() - 1;
	if (this->_context.second.empty())
		throw "Error open context";
	if (!this->_context.second.compare("server") && this->_context.first == true)
		throw "Error open context (double open)";
	if (!this->_context.second.compare("location") && this->_context.first == true)
		throw "Error open context (double open)";
}
