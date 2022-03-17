#include "Server.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	try {
		Server serv(6667);
		serv.run();
	} catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
	return 0;
}
