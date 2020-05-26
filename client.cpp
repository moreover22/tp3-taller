
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <string.h>
#include <arpa/inet.h>

#include "client_Client.h"

#define ARGV_HOST 1
#define ARGV_PORT 2

int main(int argc, const char* argv[]) {
    try {
        Client client(argv[ARGV_HOST], argv[ARGV_PORT]);
        client.run();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
