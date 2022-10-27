#include "../../include/parser/Parser.hpp"


void Parser::showData() {
    std::cout << this->_servers.size() << std::endl;
    for (size_t i = 0; i < this->_servers.size(); i++) {
        std::cout << "Server name: ";
        for (size_t j = 0; j < this->_servers.at(i)._serverName.size(); j++) {
            std::cout << this->_servers.at(i)._serverName.at(j) << ", ";
        }
        std::cout << std::endl;
        std::cout << "Listen address: " << this->_servers.at(i)._listenPort._address << std::endl;
        std::cout << "Listen port: " << this->_servers.at(i)._listenPort._port << std::endl;
        if (this->_servers.at(i)._listenPort._isDefault)
            std::cout << "Default server " << this->_servers.at(i)._listenPort._isDefault << std::endl;
        std::cout << "Count locations in server: " << this->_servers.at(i)._locations.size() << std::endl;

        for (size_t j = 0; j < this->_servers.at(i)._locations.size(); j++) {
            std::cout << "Path location: " << this->_servers.at(i)._locations.at(j)._path << std::endl;
            std::cout << "Max body size: " << this->_servers.at(i)._locations.at(j)._clientMaxBodySize << std::endl;
            std::cout << "Methods: ";
            for (size_t c = 0; c < this->_servers.at(i)._locations.at(j)._method.size(); c++) {
                std::cout << this->_servers.at(i)._locations.at(j)._method.at(c) << ", ";

            }
            std::cout << std::endl;
            std::cout << "Index: ";
            for (size_t c = 0; c < this->_servers.at(i)._locations.at(j)._index.size(); c++) {
                std::cout << this->_servers.at(i)._locations.at(j)._index.at(c) << ", ";

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


void Parser::checkDefaultServers() {
    size_t countDefaultServers;
    ListenPort tmp;
    vector<pair<int, ListenPort> > uniqueHosts;
    vector<pair<int, ListenPort> >::iterator it;

    for (size_t i = 0; i < this->_servers.size(); i++) {
        tmp._port = this->_servers.at(i)._listenPort._port;
        tmp._address = this->_servers.at(i)._listenPort._address;
        tmp._isDefault = this->_servers.at(i)._listenPort._isDefault;
        it = std::find(uniqueHosts.begin(), uniqueHosts.end(),
                       pair<int, ListenPort>(0, ListenPort(tmp._address, tmp._port, tmp._isDefault)));
        if (it == uniqueHosts.end())
            uniqueHosts.push_back(pair<int, ListenPort>(i, ListenPort(tmp._address, tmp._port, tmp._isDefault)));
        else {
            if (tmp._isDefault == true && (*it).second._isDefault == false) {
                uniqueHosts.erase(it);
                uniqueHosts.push_back(pair<int, ListenPort>(i, ListenPort(tmp._address, tmp._port, tmp._isDefault)));
            } else if (tmp._isDefault == true && (*it).second._isDefault == true)
                throw "Too much default_servers for one port listen";

        }
    }
    for (size_t i = 0; i < uniqueHosts.size(); i++)
        this->_servers.at(uniqueHosts.at(i).first)._listenPort._isDefault = true;

}

void Parser::fillServers() {
    for (size_t i = 0; i < this->_servers.size(); i++) {
        for (size_t j = 0; j < this->_servers.at(i)._locations.size(); j++) {
            if (this->_servers.at(i)._locations.at(j)._root.empty())
                this->_servers.at(i)._locations.at(j)._root = this->_servers.at(i)._root;
            if (!this->_servers.at(i)._locations.at(j)._clientMaxBodySize)
                this->_servers.at(i)._locations.at(j)._clientMaxBodySize = this->_servers.at(i)._clientMaxBodySize;
            if (!this->_servers.at(i)._locations.at(j)._errorPage.code &&
                this->_servers.at(i)._locations.at(j)._errorPage.path.empty())
                this->_servers.at(i)._locations.at(j)._errorPage = this->_servers.at(i)._errorPage;
            if (!this->_servers.at(i)._locations.at(j)._return.code &&
                this->_servers.at(i)._locations.at(j)._return.path.empty())
                this->_servers.at(i)._locations.at(j)._return = this->_servers.at(i)._return;
            if (this->_servers.at(i)._locations.at(j)._index.empty())
                this->_servers.at(i)._locations.at(j)._index = this->_servers.at(i)._index;
        }
    }
    checkDefaultServers();

}


void Parser::eraseComment(string &line) {
    string::iterator it;

    for (it = line.begin(); it != line.end(); it++) {
        if (*it == '#') {
            it = line.erase(it, line.end());
            break;
        }
    }
//	std::cout << line << std::endl;

// тоесть если будет вот такой текст
// server #{} tut tipa server nachinaetsya
// location / # tut u nas location
// то эти строчки не обработаются, но ведь они валдиные), еще одна причина не смотреть на линию с конца
}
// когда принимаешь линию отчищай ее от пробелов в начале и конце
// тогда ты получишь либо пустую строку либо команду
// пустая строка это не ошибка
// но в пустой строке странно делать ошибку если там оказался пробел


// 	if (beginCommand == line.end()) // именно тут у тя кидается ошибка в случае если линия состояла из пробелов или табов
// 		throw "Invalid syntax file (without ; or {})";
// // зачем идти с конца если у тебя есть ожидаеммые ключевые слова и если слово не ожидаемо то ошибка
// 	for (endCommand = beginCommand; endCommand != line.end(); endCommand++)
// 	{
// 		if (*endCommand == ';' || *endCommand == '}' || *endCommand == '{')
// 			break ;
// 	}
// 	if (endCommand == line.end())
// 		throw "Invalid syntax file (without ; or {})";

// 	for (endCommand++; endCommand != line.end(); )
// 	{
// 		if (*endCommand != ' ' && *endCommand != '\t')
// 			throw "Invalid syntax file (without ; or {})";
// 		endCommand = line.erase(endCommand);
// 	}

// 	return 0;
// }
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



void Parser::initData() {
    unsigned int countServers;
    unsigned int countLocations;
    vector<string>::iterator ptr;
    this->_context.second = string();

    for (ptr = this->conf.begin(); ptr != this->conf.end(); ptr++) {
        //std::cout << "Data: " << *ptr << std::endl;
        if (!(*ptr).compare("server")) {
            this->_servers.push_back(Serv());
            this->_context.second = "server";
            countServers = _servers.size() - 1;
        } else if (!(*ptr).compare("location")) {
            this->_servers.at(countServers).initLocation(ptr);
            this->_context.second = "location";
            countLocations = this->_servers.at(countServers)._locations.size() - 1;
        } else if (!(*ptr).compare("{"))
            continue;
        else if (!(*ptr).compare("}")) {
            if (!this->_context.second.compare("location"))
                this->_context.second = "server";
            else if (!this->_context.second.compare("server"))
                this->_context.second = string();
        } else {
            if (!this->_context.second.compare("server"))
                this->_servers.at(countServers).initDirective(ptr);
            else if (!this->_context.second.compare("location"))
                this->_servers.at(countServers)._locations.at(countLocations).initDirective(ptr);
        }
    }
}

void Parser::checkEndDirective(vector<string>::iterator &ptr) {
    if ((*ptr).compare(";"))
        throw "Invalid syntax file (without ;)";
    // ptr = this->conf.erase(ptr);
    // ptr--;
}

void Parser::validationDirectiveRoot(vector<string>::iterator &ptr) {
    ptr = ptr + 2;
    checkEndDirective(ptr);

}

void Parser::validationDirectiveMaxBodySize(vector<string>::iterator &ptr) {
    size_t pos;

    ptr++;

    stoul(*ptr, &pos);
    if (pos < (*ptr).size())
        throw "Invalid syntax file: error format argument";
    ptr++;
    checkEndDirective(ptr);

}


void Parser::validationDirectiveErrorPage(vector<string>::iterator &ptr) {
    size_t pos;

    ptr++;

    stoul((*ptr), &pos);

    if (pos < (*ptr).size())
        throw "Invalid syntax file: error format arg";

    ptr = ptr + 2;

    checkEndDirective(ptr);


}

void Parser::validationDirectiveLimitExcept(vector<string>::iterator &ptr) {
    size_t i = 0;
    size_t maxCountArgs = 4;

    ptr++;

    while ((*ptr).compare(";") && ptr != conf.end()) {
        if ((*ptr).compare("GET") && (*ptr).compare("POST") && (*ptr).compare("DELETE"))
            throw "Error name arg in command limit except";
        // if (!(*ptr).compare(";"))
        // 	break ;
        ptr++;
        i++;
    }
    if (i == 0 || i > maxCountArgs)
        throw "Unvalid count arguments";
    checkEndDirective(ptr);
}

void Parser::validationDirectiveServerName(vector<string>::iterator &ptr) {
    size_t i = 0;
    while ((*ptr).compare(";") && ptr != conf.end()) {
        // if (!(*ptr).compare(";"))
        // 	break ;
        ptr++;
        i++;
    }
    if (i == 0)
        throw "Unvalid count arguments";
    checkEndDirective(ptr);
}

void Parser::validationDirectiveIndex(vector<string>::iterator &ptr) {
    size_t i = 0;
    while ((*ptr).compare(";") && ptr != conf.end()) {
        // if (!(*ptr).compare(";"))
        // 	break ;
        ptr++;
        i++;
    }
    if (i == 0)
        throw "Unvalid count arguments";
    checkEndDirective(ptr);
}

void Parser::validationDirectiveReturn(vector<string>::iterator &ptr) {
    size_t pos;

    ptr++;

    stoul((*ptr), &pos);

    if (pos < (*ptr).size())
        throw "Invalid syntax file: error format arg";

    ptr = ptr + 2;

    checkEndDirective(ptr);
}

void Parser::validationDirectiveListen(vector<string>::iterator &ptr) {
    size_t i = 0;
    ListenPort listen;
    string path = *ptr;

    ptr++;
    parseListenPath(path, listen);
    ptr++;
    if ((*ptr).compare(";") && (*ptr).compare("default_server"))
        throw "Error sign default_server";
    if (!(*ptr).compare("default_server"))
        ptr++;
    checkEndDirective(ptr);

}

void Parser::split(string &line) {
    char delimiter;
    size_t pos = 0;
    int posSpace = 0;
    int posTab = 0;

    while (pos != std::string::npos) {
        posSpace = line.find(' ');
        posTab = line.find('\t');
        if (posSpace == std::string::npos && posTab == std::string::npos)
            break;
        pos = posSpace;
        if ((posSpace == std::string::npos && posTab != std::string::npos)
            || (posSpace > posTab && posTab != std::string::npos))
            pos = posTab;
        delimiter = line.at(pos);
        if (pos != 0 && !line.empty())
            this->conf.push_back(line.substr(0, pos));
        while (pos < line.size() && line.at(pos) == delimiter) {
            pos++;
        }
        line.erase(0, pos);
    }

    //std::cout << line << std::endl;
    if (!line.empty())
        this->conf.push_back(line);

    if (this->conf.at(this->conf.size() - 1).end().operator--().operator*() == ';'
        && this->conf.at(this->conf.size() - 1).size() > 1) {
        this->conf.at(this->conf.size() - 1).erase(this->conf.at(this->conf.size() - 1).end().operator--());
        this->conf.push_back(";");
    }

}

void Parser::validationServer(vector<string>::iterator &ptr) {
    if (!this->_context.second.empty())
        throw "Error context server";
    ptr++;
    if ((*ptr).compare("{"))
        throw "Error open context server";
    this->_context.first = true;
    this->_context.second = "server";
}

void Parser::validationDirective(vector<string>::iterator &ptr) {
    validationContextDirective(ptr);
    if (!(*ptr).compare("listen"))
        validationDirectiveListen(ptr);
    else if (!(*ptr).compare("root"))
        validationDirectiveRoot(ptr);
    else if (!(*ptr).compare("client_max_body_size"))
        validationDirectiveMaxBodySize(ptr);
    else if (!(*ptr).compare("error_page"))
        validationDirectiveErrorPage(ptr);
    else if (!(*ptr).compare("server_name"))
        validationDirectiveServerName(ptr);
    else if (!(*ptr).compare("index"))
        validationDirectiveIndex(ptr);
        // else if (!(*ptr).compare("cgi_extension"))
        // 	validationDirectiveCgiExtension(ptr);
        // else if (!(*ptr).compare("cgi_path"))
        // 	validationDirectiveCgiPath(ptr);
    else if (!(*ptr).compare("return"))
        validationDirectiveReturn(ptr);
    else if (!(*ptr).compare("limit_except"))
        validationDirectiveLimitExcept(ptr);
    else
        throw "Error name directive";

    //erase ';' и может {} тоже удалять
}

void Parser::validationLocation(vector<string>::iterator &ptr) {
    if (this->_context.second.compare("server"))
        throw "Error context location";
    ptr = ptr + 2;
    if ((*ptr).compare("{"))
        throw "Error open context location";
    this->_context.first = true;
    this->_context.second = "location";
}


void Parser::validationConfig(string &line) {
    int count = this->conf.size();
    //split(line);
    vector<string>::iterator ptr;
    if (!this->conf.size())
        throw "Empty config";
    for (ptr = this->conf.begin(); ptr != this->conf.end(); ptr++) {
        //std::cout << *ptr << std::endl;
        if (!(*ptr).compare("server"))
            validationServer(ptr);
        else if (!(*ptr).compare("location"))
            validationLocation(ptr);
        else if (!(*ptr).compare("}"))
            validationCloseContext(ptr);
        else if (!(*ptr).compare("{"))
            validationOpenContext(ptr);
        else
            validationDirective(ptr);
    }


}

void Parser::parse(const string &filename) {
    std::ifstream fin(filename, ios_base::in);
    std::string line;
    std::string command;

    if (!fin.is_open())
        throw "Failed to open file";

    while (!fin.eof()) {
        std::getline(fin, line);
        if (line.empty())
            continue;
        eraseComment(line);
        split(line);
    }
    validationConfig(line);
    initData();
    std::for_each(this->conf.begin(), this->conf.end(), [](const auto &e) { std::cout << e << "\n"; });
    // //Заполнение объектов отсутствующими значениями
//	fillServers();
    // //Добавить метод для проверки обязательных параметров
//	showData();

}
