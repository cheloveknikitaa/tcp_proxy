// #include "../../include/parser/Utils.hpp"
#include "../../include/parser/Parser.hpp"


string popBackArg(string &args)
{
	string arg;
	arg = args;
	string::iterator ptr;
	string::iterator ptrLine;

	ptrLine = args.end();

	for (ptr = arg.end().operator--(); ptr != arg.begin(); ptr--)
	{
		if (*ptr == '\t' || isspace(*ptr))
			break ;
		ptrLine--;
	}
	if (arg.begin() != ptr)
		arg.erase(arg.begin(), ptr.operator++());
	args.erase(ptrLine, args.end());

	return arg;
}

void	eraseCommand(string &args)
{
	string::iterator it;
	for (it = args.begin(); it != args.end(); )
	{
		if (isprint(*it) && !isspace(*it))
			break ;
		it = args.erase(it);
	}
	if (it == args.end())
		throw "Error: not enought args";
	for (string::iterator ite = args.end().operator--(); ite != args.begin(); ite--)
	{
		if (isprint(*ite) && !isspace(*ite))
			break ;
		ite = args.erase(ite);
	}
	//std::cout << args << std::endl;
}


unsigned int	checkCountArgs(string &args)
{

	eraseCommand(args);
	int count = 1;
	for (string::iterator it = args.begin(); it != args.end(); it++)
	{
		if (*it == ' ' || *it == '\t')
		{
			count += 1;
			for (string::iterator ite = it; ite != args.end(); ite++)
			{
				if (isprint(*ite) && !isspace(*ite))
					break ;
				it = ite;
			}
		}
	}

	return count;
}

void	checkAddress(string &address)
{
	string::iterator it;
	vector <unsigned int> count(1);
	

	for (it = address.begin(); it != address.end(); it++)
	{
		// server_name == имени хоста?
		if (!isalpha(*it))
			break ;
	}
	if (it == address.end())
		return ;
	for (it = address.begin(); it != address.end(); it++)
	{
		
		if (*it == '.')
		{
			if (count.at(count.size() - 1) > 0 && count.at(count.size() - 1) < 4)
			{
				count.push_back(0);
				continue ;
			}
			else
				throw "Invalid value address";
		}
		count.at(count.size() - 1)++;
	}
	if (count.size() != 4)
		throw "Invalid value address";
}

void	parseListenPath(string &path, ListenPort & listen)
{
	//validation ip - Inet_aton
	string::iterator it;
	string::iterator ite;
	size_t pos;
	string address;
	address = path;
	ite = address.begin();

	//without ipv6
	// Обрабатываемые кейсы:
	// listen 127.0.0.1:8000;
	// listen 127.0.0.1;
	// listen 8000;
	// listen *:8000;
	// listen localhost:8000;

	for (it = path.begin(); it != path.end(); it++)
	{
		if (*it == ':')
			break ;
		ite++;
	}
	if (it == path.end())
	{
		for (it = path.begin(); it != path.end(); it++)
		{
			if (isalpha(*it) || *it == '.')
				break ;
		}
		if (it != path.end())
		{
			checkAddress(path);
			listen._address = path;
			listen._port = 80;
		}
		else
		{
			listen._port =  stoul(path, &pos);
			std::cout << listen._port << std::endl;
			if (pos < path.size())
				throw "Invalid value port";
			listen._address = "0.0.0.0";
		}
	}
	else 
	{
		if (*it == ':' && *(path.begin()) == '*')
			listen._address = "0.0.0.0";
		else 
		{
			address.erase(ite, address.end());
			checkAddress(address);
			listen._address = address;
			path.erase(path.begin(), it.operator++());
			listen._port =  stoul(path, &pos);
			if (pos < path.size())
				throw "Invalid value port";
		}
	}
	
}

