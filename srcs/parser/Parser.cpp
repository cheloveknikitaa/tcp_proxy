#include "../../include/parser/Parser.hpp"


void	Parser::showData()
{
	std::cout << this->_servers.size() << std::endl;
	for (size_t i = 0; i < this->_servers.size(); i++)
	{
		std::cout << "Server name: ";
		for (size_t j = 0; j < this->_servers.at(i)._serverName.size(); j++)
		{
			std::cout << this->_servers.at(i)._serverName.at(j) << ", ";
		}
		std::cout << std::endl;
		std::cout << "Listen address: " << this->_servers.at(i)._listenPort._address << std::endl;
		std::cout << "Listen port: " << this->_servers.at(i)._listenPort._port << std::endl;
		if (this->_servers.at(i)._listenPort._isDefault)
			std::cout << "Default server " << this->_servers.at(i)._listenPort._isDefault << std::endl;
		std::cout << "Count locations in server: " << this->_servers.at(i)._locations.size() << std::endl;

		for (size_t j = 0; j < this->_servers.at(i)._locations.size(); j++)
		{
			std::cout << "Path location: " << this->_servers.at(i)._locations.at(j)._path << std::endl;
			std::cout << "Max body size: " << this->_servers.at(i)._locations.at(j)._clientMaxBodySize << std::endl;
			std::cout << "Methods: ";
			for (size_t c = 0; c < this->_servers.at(i)._locations.at(j)._method.size(); c++)
			{
				std::cout << this->_servers.at(i)._locations.at(j)._method.at(c) << ", ";

			}
			std::cout << std::endl;
			std::cout << "Code error page: " << this->_servers.at(i)._locations.at(j)._errorPage.code << std::endl;
			std::cout << "Path error page: " << this->_servers.at(i)._locations.at(j)._errorPage.path << std::endl;
			std::cout << "Code return: " << this->_servers.at(i)._locations.at(j)._return.code << std::endl;
			std::cout << "Path return: " << this->_servers.at(i)._locations.at(j)._return.path << std::endl;
			std::cout << "Path root: " << this->_servers.at(i)._locations.at(j)._root << std::endl;
			std::cout << std::endl;
		
		}
		std::cout << std::endl;
		
	}
}



void	Parser::checkDefaultServers()
{
	size_t countDefaultServers;
	ListenPort tmp;
	vector <pair<int, ListenPort> > uniqueHosts;
	vector <pair<int, ListenPort> >::iterator it;
	
	for (size_t i = 0; i < this->_servers.size(); i++)
	{
		tmp._port = this->_servers.at(i)._listenPort._port;
		tmp._address = this->_servers.at(i)._listenPort._address;
		tmp._isDefault = this->_servers.at(i)._listenPort._isDefault;
		it = std::find(uniqueHosts.begin(), uniqueHosts.end(), pair<int, ListenPort>(0, ListenPort(tmp._address, tmp._port, tmp._isDefault)));
		if (it == uniqueHosts.end())
			uniqueHosts.push_back(pair<int, ListenPort>(i, ListenPort(tmp._address, tmp._port, tmp._isDefault)));
		else
		{
			if (tmp._isDefault == true && (*it).second._isDefault == false)
			{
				uniqueHosts.erase(it);
				uniqueHosts.push_back(pair<int, ListenPort>(i, ListenPort(tmp._address, tmp._port, tmp._isDefault)));
			}
			else if (tmp._isDefault == true && (*it).second._isDefault == true)
				throw "Too much default_servers for one port listen";
				
		}	
	}
	for (size_t i = 0; i < uniqueHosts.size(); i++)
		this->_servers.at(uniqueHosts.at(i).first)._listenPort._isDefault = true;

}

void	Parser::fillServers()
{
	for (size_t i = 0; i < this->_servers.size(); i++)
	{
		for (size_t j = 0; j < this->_servers.at(i)._locations.size(); j++)
		{
			if (this->_servers.at(i)._locations.at(j)._root.empty())
				this->_servers.at(i)._locations.at(j)._root = this->_servers.at(i)._root;
			if (!this->_servers.at(i)._locations.at(j)._clientMaxBodySize)
				this->_servers.at(i)._locations.at(j)._clientMaxBodySize = this->_servers.at(i)._clientMaxBodySize;
			if (!this->_servers.at(i)._locations.at(j)._errorPage.code && this->_servers.at(i)._locations.at(j)._errorPage.path.empty())
				this->_servers.at(i)._locations.at(j)._errorPage = this->_servers.at(i)._errorPage;
			if (!this->_servers.at(i)._locations.at(j)._return.code && this->_servers.at(i)._locations.at(j)._return.path.empty())
				this->_servers.at(i)._locations.at(j)._return = this->_servers.at(i)._return;
		}
	}
	checkDefaultServers();
	
}


bool	Parser::checkComment(string &line)
{
	string::iterator startLine;

	for (startLine = line.begin(); startLine != line.end(); startLine++)
	{
		if (*startLine == '#')
			return true;
	}
	return false;

}

int	Parser::eraseLine(string &line)
{
	string::iterator beginCommand;
	string::iterator endCommand;
	

	for (beginCommand = line.begin(); beginCommand != line.end(); )
	{	
		if (!isalpha(*beginCommand) && *beginCommand != '}' && *beginCommand != '{')
		{
			if (*beginCommand != ' ' && *beginCommand != '\t')
				throw "Invalid syntax file (without ; or {})";
			beginCommand = line.erase(beginCommand);
		}
		else
			break ;
	}

	if (beginCommand == line.end()) 
		throw "Invalid syntax file (without ; or {})";

	for (endCommand = beginCommand; endCommand != line.end(); endCommand++)
	{
		if (*endCommand == ';' || *endCommand == '}' || *endCommand == '{')
			break ;
	}
	if (endCommand == line.end())
		throw "Invalid syntax file (without ; or {})";

	for (endCommand++; endCommand != line.end(); )
	{
		if (*endCommand != ' ' && *endCommand != '\t')
			throw "Invalid syntax file (without ; or {})";
		endCommand = line.erase(endCommand);
	}

	return 0;
}

string Parser::getCommand(string &line)
{
	string command = line;
	string::iterator ptr;
	string::iterator ptrLine = line.begin();

	for (ptr = command.begin(); ptr != command.end(); ptr++)
	{
		if (*ptr == ' ' || *ptr == '{' || *ptr == '}')
			break ;
		ptrLine.operator++();
	}
	if (ptrLine == line.end())
		throw "Error final command";
	if (*ptr == '}')
		return command;
	command.erase(ptr, command.end());
	line.erase(line.begin(), ptrLine);
	return command;
}

void	Parser::initData(string command, string line)
{
	unsigned int countServers = _servers.size() - 1;
	//std::cout << line << std::endl;

	if (!command.compare("server"))
		this->_servers.push_back(Serv());
	else if (!command.compare("location"))
		this->_servers.at(countServers).initLocation(line);
	else
	{
		unsigned int countLocation = this->_servers.at(countServers)._locations.size() - 1;
		if (!this->_context.second.compare("server"))
			this->_servers.at(countServers).initDirective(line, command);
		else if (!this->_context.second.compare("location"))
			this->_servers.at(countServers)._locations.at(countLocation).initDirective(line, command);
		else
			throw "Error context for command";
	}
}

void	Parser::parse(const string &filename)
{
	std::ifstream fin(filename, ios_base::in);
	std::string line;
	std::string command;

	if (!fin.is_open())
		throw "Failed to open file";
	
	while (!fin.eof()) {
		std::getline(fin,line);
		if (!checkComment(line) && !line.empty() && !eraseLine(line))
		{
			command = getCommand(line);
			//std::cout << command << std::endl;
			checkContext(command, *(line.end().operator--()));
			if (command.size() > 1)
				initData(command, line);
		}
	}
	//Заполнение объектов отсутствующими значениями
	fillServers();
	//Добавить метод для проверки обязательных параметров
	showData();

}
