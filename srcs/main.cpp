#include "Server.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
	signal(SIGTERM, sigHendler);
	signal(SIGINT, sigHendler);
	if (argc != 2){
		cerr << "try ./build/apps/proxy_server 'port for server'\n";
		return -1;
	}
	try {
		Server serv(stoi(argv[1]));
		serv.run();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
