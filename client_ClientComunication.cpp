#include "client_ClientComunication.h"
#include <netinet/in.h>

#define SIZEOF_UINT16 2

int ClientCommunication::send(const char* buffer, size_t len) {
    return client.send(buffer, len);
}

int ClientCommunication::receive() {
    uint16_t len_msg;
    client.receive((char *) &len_msg, SIZEOF_UINT16);
    len_msg = ntohs(len_msg);
    buffer_response.resize(len_msg);
    client.receive(&buffer_response[0], len_msg);
    buffer_response[len_msg] = 0;
    return 0;
}

void ClientCommunication::show_response() {
    printf("%s\n", buffer_response.c_str());
}

bool ClientCommunication::is_finished() {
    return buffer_response == "Perdiste" || buffer_response == "Ganaste";
}
