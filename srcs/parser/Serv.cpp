// #include "../../include/parser/Utils.hpp"
#include "../../include/parser/Parser.hpp"


void	Serv::processingCommandListen(string &line)
{
	string args = line;
	vector <string> argsTmp;
	ListenPort listen;

	int countArgs = checkCountArgs(args);
	if (countArgs > 2)
		throw "Error count args in command listen";

	for (size_t i = 0; i < countArgs; i++)
	{
		argsTmp.push_back(popBackArg(args));
		eraseCommand(args);
	}
	if (countArgs == 2)
	{
		if (argsTmp.at(0).compare("default_server"))
			throw "Error sign default_server";
		listen._isDefault = true;
		parseListenPath(argsTmp.at(1), listen);
	}
	else
		parseListenPath(argsTmp.at(0), listen);

	this->_listenPort = listen;


}

void	Serv::processingCommandRoot(string &line)
{
	string args = line;
	string argTmp;

	int countArgs = checkCountArgs(args);
	if (countArgs > 1)
		throw "Error count args in command root";
	

	argTmp = popBackArg(args);
	this->_root = argTmp;


}

void	Serv::processingCommandMaxBodySize(string &line)
{
	string args = line;
	string argTmp;
	size_t pos;


	int countArgs = checkCountArgs(args);
	if (countArgs > 1)
		throw "Error count args in command MaxBodySize";

	argTmp = popBackArg(args);
	
	this->_clientMaxBodySize = stoul(argTmp, &pos);
	if (pos < argTmp.size())
		throw "Invalid syntax file: error format arg";

}

void	Serv::processingLimitExcept(string &line)
{

	string args = line;
	vector <string> methods;
	string argTmp;

	int countArgs = checkCountArgs(args);
	if (countArgs > 3)
		throw "Error count args in command server name";
	
	for (size_t i = 0; i < countArgs; i++)
	{
		argTmp = (popBackArg(args));
		if (!argTmp.compare("GET") || !argTmp.compare("POST") || !argTmp.compare("DELETE"))
			methods.push_back(argTmp);
		else
			throw "Error name arg in command limit except";
		eraseCommand(args);
	}
	this->_method = methods;
	
}

void	Serv::processingErrorPage(string &line)
{
	string args = line;
	vector <string> argsTmp;
	size_t pos;
	
	int countArgs = checkCountArgs(args);
	if (countArgs > 2)
		throw "Error count args in command Error Page";

	for (size_t i = 0; i < countArgs; i++)
	{
		argsTmp.push_back(popBackArg(args));
		eraseCommand(args);
	}

	this->_errorPage.code = stoul(argsTmp.at(1), &pos);
	this->_errorPage.path = argsTmp.at(0);

	if (pos < argsTmp.at(1).size())
		throw "Invalid syntax file: error format arg";
}

void	Serv::processingServerName(string &line)
{
	string args = line;
	vector <string> argsTmp;

	int countArgs = checkCountArgs(args);

	for (size_t i = 0; i < countArgs; i++)
	{
		argsTmp.push_back(popBackArg(args));
		eraseCommand(args);
	}
	
	this->_serverName = argsTmp;
}

void	Serv::processingCgiExtension(string &line)
{

}

void	Serv::processingCgiPath(string &line)
{

}

void	Serv::processingReturn(string &line)
{
	string args = line;
	vector <string> argsTmp;
	size_t pos;
	
	int countArgs = checkCountArgs(args);
	if (countArgs > 2)
		throw "Error count args in command Return";

	for (size_t i = 0; i < countArgs; i++)
	{
		argsTmp.push_back(popBackArg(args));
		eraseCommand(args);
	}

	this->_return.code = stoul(argsTmp.at(1), &pos);
	this->_return.path = argsTmp.at(0);

	if (pos < argsTmp.at(1).size())
		throw "Invalid syntax file: error format arg";
}

void	Serv::initLocation(string &line)
{
	string path = line;
	this->_locations.push_back(Location());
	unsigned int countLocation = this->_locations.size() - 1;

	path.erase(path.find('{'));
	if (checkCountArgs(path) > 1)
		throw "Error count path";
	this->_locations.at(countLocation)._path = path;

};


void	Serv::initDirective(string &line, string &command)
{

	line.erase(line.find(';'));

	if (!command.compare("listen"))
		processingCommandListen(line);
	else if(!command.compare("root"))
		processingCommandRoot(line);
	else if (!command.compare("client_max_body_size"))
		processingCommandMaxBodySize(line);
	else if (!command.compare("error_page"))
		processingErrorPage(line);
	else if (!command.compare("server_name"))
		processingServerName(line);
	else if (!command.compare("cgi_extension"))
		processingCgiExtension(line);
	else if (!command.compare("cgi_path"))
		processingCgiPath(line);
	else if (!command.compare("return"))
		processingReturn(line);
	else
		throw "Error name command";

}