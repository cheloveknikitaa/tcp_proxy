// // #include "../../include/parser/Serv.hpp"
// #include "../../include/parser/Location.hpp"
#include "../../include/parser/Parser.hpp"

void	Location::initDirective(string &line, string &command)
{

	line.erase(line.find(';'));

	if(!command.compare("root"))
		processingCommandRoot(line);
	else if (!command.compare("client_max_body_size"))
		processingCommandMaxBodySize(line);
	else if (!command.compare("limit_except"))
		processingLimitExcept(line);
	else if (!command.compare("error_page"))
		processingErrorPage(line);
	else if (!command.compare("cgi_extension"))
		processingCgiExtension(line);
	else if (!command.compare("cgi_path"))
		processingCgiPath(line);
	else if (!command.compare("return"))
		processingReturn(line);
	else
		throw "Error name command";

}