#ifndef SERVER_CLIENTLISTENER_H
#define SERVER_CLIENTLISTENER_H

#include "server_CircularQueue.h"
#include "server_PeerClient.h"
#include "common_Socket.h"
#include <vector>
#include <map>

class ClientListener {
private:
    std::vector<PeerClient *> clients;
    Socket& skt;
    CircularQueue& c_queue;
    Statistics& stats;
    std::map<char, Operation*> operations;
public:
    ClientListener(Socket& skt, CircularQueue& c_queue, Statistics& stats): 
                                skt(skt), c_queue(c_queue), stats(stats) {}
    void listen();
    void stop_listening();
    ~ClientListener();
};

#endif
