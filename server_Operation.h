#ifndef SERVER_OPERATION_H
#define SERVER_OPERATION_H

#include "server_PeerClient.h"
#include "common_NumberValidator.h"

class Operation {
public:
    virtual void operator()(PeerClient& peer_client) = 0;
};

class OperationHelp: public Operation {
public:
    void operator()(PeerClient& peer_client);
};

class OperationSurrender: public Operation {
public:
    void operator()(PeerClient& peer_client);
};

class OperationCheckNumber: public Operation {
private:
    NumberValidator validator;
public:
    void operator()(PeerClient& peer_client);
};
#endif
