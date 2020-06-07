#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include "client_ClientComunication.h"
#include "client_InputCommand.h"
#include "common_Socket.h"
#include "client_SocketClientConf.h"
#include "common_NumberValidator.h"

class Client {
private:
    SocketClientConf socket_conf;
    Socket socket;
    ClientCommunication communication;
    InputCommand commands;
    NumberValidator validator;
public:
    Client(const char* host, const char* port);
    void run();
};

#endif
