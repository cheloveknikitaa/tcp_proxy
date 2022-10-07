#include "../include/Parser.hpp"

bool	check_comment(string &line)
{
	string::iterator startLine;

	for (startLine = line.begin(); startLine != line.end(); startLine++)
	{
		if (*startLine == '#')
			return true;
	}
	return false;

}

void	erase_space(string::iterator &startLine, char c, string::iterator &offsetLine, std::string &line)
{
	unsigned int count = std::count(startLine, offsetLine, c);
	for (size_t i = count; i > 0; i--) 
		line.erase(std::find(startLine, offsetLine, c));
}

int	erase_line(string &line)
{
	string::iterator startLine;
	string::iterator tmpLine;
	string::iterator endLine;

	for (startLine = line.begin(); startLine != line.end(); startLine++)
	{
		if (isalpha(*startLine) || *startLine == '}' || *startLine == '{')
			break ;
	}
	if (startLine == line.end()) 
		return 1;
	
	tmpLine = line.begin();
	erase_space(tmpLine, ' ', startLine, line);
	erase_space(tmpLine, '\t', startLine, line);

	for (endLine = startLine; endLine != line.end(); endLine++)
	{
		if (*endLine == ';')
			break ;
	}
	if (endLine == line.end())
		throw "Invalid syntax file (without ;)";
		//std::cout << line << std::endl;
	tmpLine = line.end();
	erase_space(endLine, ' ', tmpLine, line);
	erase_space(endLine, '\t', tmpLine, line);
	
	unsigned int count = std::count(endLine, line.end(), ';');
	if (count > 1)
		throw "Invalid syntax file (many ;)";
	line.erase(line.find(';', 1));
	std::cout << line << std::endl;

	return 0;
}

void	parse_line(string &line)
{

}

void	Parser::parse(const string &filename)
{
	//std::cout << filename;
	std::ifstream fin(filename, ios_base::in);
	std::string line;

	if (!fin.is_open())
		throw "Failed to open file";
	
	while (!fin.eof()) {
		std::getline(fin,line);
		if (!check_comment(line) && !line.empty() && !erase_line(line))
		{
			parse_line(line);	
		}
		//std::cout << line << std::endl;
		// if (!check_comment(line) && !line.empty() && !erase_line(line))
		// 	parse_line(line);	
	}
	
}