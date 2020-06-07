#include "server_Server.h"
#include "server_NumberParser.h"
#include <iostream>
#include <string>


Server::Server(const char* service, const char* number_path): 
                        socket(socket_server_conf), listener(socket, cq, stat) {
    NumberParser parser(number_path);
    parser.parse(cq);
    socket.bind_and_listen(service);
    start();
    listener.listen();
}

void Server::run() {
    std::string input;
    bool quit = false;
    while (!quit) {
        std::cin >> input;
        if (input == "q") {
            listener.stop_listening();
            quit = true;
        }
    }
}

void Server::show_statistics() {
    stat.show();
}
