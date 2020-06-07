#ifndef CLIENT_CLIENTCOMUNICATION_H
#define CLIENT_CLIENTCOMUNICATION_H

#include "common_Socket.h"
#include <string>

class ClientCommunication: public ISendable {
private:
    std::string buffer_response;
    bool new_information = false;
    Socket& client;
public:
    explicit ClientCommunication(Socket& socket): client(socket) {}
    int send(const char* buffer, size_t len) override;
    int receive();
    void show_response();
    bool is_finished();
};
#endif
