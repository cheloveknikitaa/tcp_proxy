#include "../../include/parser/Parser.hpp"

int main(int argc, char **argv)
{
	Parser parser;
	
	try {
		if (argc != 2)
			throw "Wrong number of arguments";
		string file = string(argv[1]);
		parser.parse(file);
	}
	catch ( char const * e )
	{
		// доделать вывод сообщения из throw
		cout << "Error: " << e << std::endl;
	}
}