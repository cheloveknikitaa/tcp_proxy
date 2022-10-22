#pragma once
#include "../Utils.hpp"
#include "Serv.hpp"
#include "Utils.hpp"
#include "Location.hpp"

class Parser
{
private:
	vector <Serv> _servers;
	pair <bool, string> _context;

	int		eraseLine(string &line);
	bool	checkComment(string &line);
	void	checkDefaultServers();
	void	checkContext(string command, char lastLine);
	void	initContextServer(string command, char lastLine);
	void	initContextLocation(string command, char lastLine);
	void	initData(string command, string line);
	void	closeContext();
	void	fillServers();
	void	showData();
	string 	getCommand(string &line);

public:
	Parser(void) : _context(false, string()) {};
	void	parse(const string &filename);


	~Parser() {};
};
