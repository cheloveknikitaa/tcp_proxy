#include "Server.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
	signal(SIGTERM, sigHendler);
	signal(SIGINT, sigHendler);
	if (argc == 2){
		try {
			Server serv(stoi(argv[1]));
			serv.run();
		} catch(std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	} else {
		cerr << "try use just port for proxy, or use ip portDB port for proxy sql\n";
	}
	return 0;
}
