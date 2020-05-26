
#include <exception>
#include <iostream>

#include "server_Server.h"

#define INDEX_PORT_ARG 1
#define INDEX_FILE_ARG 2


int main(int argc, const char* argv[]) {
    try {
        Server server(argv[INDEX_PORT_ARG], argv[INDEX_FILE_ARG]);    
        server.join();
        server.show_statistics();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
