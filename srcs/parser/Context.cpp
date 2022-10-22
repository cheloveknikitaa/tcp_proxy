#include "../../include/parser/Parser.hpp"


void	Parser::initContextServer(string command, char lastLine)
{
	if (!command.compare("server"))
	{
		if (lastLine == '{')
		{
			this->_context.first = true;
			this->_context.second = "server";
		}
		else
			this->_context.second = "server";
	}
	else	
		throw "Invalid syntax file (error command context)";	
}



void	Parser::initContextLocation(string command, char lastLine)
{
	if (!command.compare("location"))
	{
		if (lastLine == '{')
		{
			this->_context.first = true;
			this->_context.second = "location";
		}
		else
			this->_context.second = "location";
	}
	else	
	{
		if (lastLine == '{')
			throw "Invalid syntax file (Error context)";
	}	
}

void	Parser::closeContext()
{
	//std::cout << "Context: " << this->_context.second << std::endl;

	if (this->_context.first == false)
		throw "Invalid syntax file (double close context)";
	if (!this->_context.second.compare("server"))
	{
		this->_context.first = false;
		this->_context.second = string();
	}
	else if (!this->_context.second.compare("location"))
		this->_context.second = "server";
	else
		throw "Invalid syntax file (Error context)";
}

void	Parser::checkContext(string command, char lastLine)
{
	//std::cout << "Context: " << this->_context.second << std::endl;
	if (command.size() == 1 && (lastLine == '{' || lastLine == '}'))
	{
		if (this->_context.second.empty())
			throw "Invalid syntax file (Error context)";
		if (lastLine == '}')
			closeContext();
		else
			throw "Invalid syntax file (Error context)";
		return ;
	}
	if (this->_context.second.empty())
		initContextServer(command, lastLine);
	else if (!this->_context.second.compare("server"))
		initContextLocation(command, lastLine);
	else {
		if (lastLine == '{')
			throw "Invalid syntax file (Error context)";
		else if (lastLine == '}')
			closeContext();
	}
}