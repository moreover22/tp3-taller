#include "client_Client.h"
#include <string>
#include <iostream>

Client::Client(const char* host, const char* port): socket(socket_conf),
                                                        communication(socket) {
    socket.connect(host, port);
}

void Client::run() {
    DefaultInputCommand default_input_command;
    HelpInputCommand help_input_command;
    SurrenderInputCommand surrender_input_command;
    commands.push("DEFAULT", &default_input_command);
    commands.push("AYUDA", &help_input_command);
    commands.push("RENDIRSE", &surrender_input_command);
    commands.set_default("DEFAULT");
    do {
        std::string input;
        std::getline(std::cin, input);
        if (input.size() == 0) continue;
        (*commands.get(input))(input, communication);
        communication.show_response();
    } while (!communication.is_finished());
}
