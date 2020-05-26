#include "client_Command.h"
#include "client_ClientComunication.h"
#include "common_IInterchangeable.h"

#include <arpa/inet.h>
#include <limits>
#include <string.h>
#include <string>

#define SIZEOF_UINT16 2

void NumberInputCommand::operator()(const std::string& input, 
                                        ClientCommunication& communication) {
    int min = std::numeric_limits<uint16_t>::min();
    int max = std::numeric_limits<uint16_t>::max();
    if (!validator.validate_range(input, min, max)) {
        return;
    }
    const char* msg = "n";
    communication.send(msg, strlen(msg));
    uint16_t number = std::stoi(input);
    number = htons(number);
    communication.send((const char *) &number, SIZEOF_UINT16);
    communication.receive();
}

void HelpInputCommand::operator()(const std::string& input,
                                        ClientCommunication& communication) {
    const char* msg = "h";
    communication.send(msg, strlen(msg));
    communication.receive();
}

void SurrenderInputCommand::operator()(const std::string& input,
                                        ClientCommunication& communication) {
    const char* msg = "s";
    communication.send(msg, strlen(msg));
    communication.receive();
}

void DefaultInputCommand::operator()(const std::string& input,
                                        ClientCommunication& communication) {
    int min = std::numeric_limits<uint16_t>::min();
    int max = std::numeric_limits<uint16_t>::max();
    if (!validator.validate_range(input, min, max)) {
        printf("Error: comando inválido. Escriba AYUDA para obtener ayuda\n");
        return;
    }
    number_command(input, communication);
}
