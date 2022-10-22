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
// тоесть если будет вот такой текст
// server #{} tut tipa server nachinaetsya
// location / # tut u nas location
// то эти строчки не обработаются, но ведь они валдиные), еще одна причина не смотреть на линию с конца
}
// когда принимаешь линию отчищай ее от пробелов в начале и конце
// тогда ты получишь либо пустую строку либо команду
// пустая строка это не ошибка
// но в пустой строке странно делать ошибку если там оказался пробел
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

	if (beginCommand == line.end()) // именно тут у тя кидается ошибка в случае если линия состояла из пробелов или табов
		throw "Invalid syntax file (without ; or {})";
// зачем идти с конца если у тебя есть ожидаеммые ключевые слова и если слово не ожидаемо то ошибка
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
// одиноковые проверки переходящие из вышестоящих функций
// делаешь слишком сложно простые вещи
// сделай функцию сплит которая будет разделать в строке значения на аргументы
// например:
//                 server    	           {                #это мы открываем блок сервер
//это строка которую мы получили ↑
// а это то вектор кторый мы получим на выходе ↓ (все что после # на не нужно это мусор)
//  [0] "server"
//  [1] "{"
// разве не просто?
// разберем другой случай когда у тебя нет '{'
//            server   # вариант без скобки
//  [0] "server"
// это значит что на следующей строке мы ожидаем обязательно '{' в 0 элементе иначе ошибка
// как нам можно совсем угареть и получить клевый парсер? верно склеить все строки в один вектор
// [0] server !ключивое слово
// [1] { !обязательное после ключа
// [2] listen !возможное ключивое слово
// [3] 127.0.0.1:80 !обязательное его продолжение
// [4] server_name !возможное ключивое слово
// [5] localhost; !обязательное его продолжение
// [6] error_page !возможное ключивое слово
// [7] 404 !обязательное его продолжение
// [8] /404.html !обязательное его продолжение
// [9] location !возможное ключивое слово
// [10] / !обязательное его продолжение
// [11] { !обязательное его продолжение
// [12] server !невозможное ключивое слово на уровне локейшн ошибка!!!

// возможные ключевые слова для разных уровней разные и нужно это регулировать появлением {} и важных блоков по типу server location(а по сути больше нету)
// как тебе такой вариант парсера???
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
