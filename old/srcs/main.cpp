#include "Server.hpp"

int main(int argc, char **argv){
    if (argc != 2) {
        std::cerr << "not enought arg\n";
        return (-1);
    }
    try {
        Server server(argv[1]);
        server.run();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
