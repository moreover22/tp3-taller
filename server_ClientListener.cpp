#include "server_ClientListener.h"
#include "server_Operation.h"
#include <map>
#include <utility>

ClientListener::ClientListener(Socket& skt, CircularQueue& c_queue, 
    Statistics& stats): skt(skt), c_queue(c_queue), stats(stats) {}

void ClientListener::listen() {
    OperationHelp help_operation;
    OperationSurrender surrender_operation;
    OperationCheckNumber check_number_operation;
    std::map<char, Operation*> operations{
        {'h', &help_operation},
        {'s', &surrender_operation},
        {'n', &check_number_operation}
    };
    while (true) {
        Socket client_skt;
        try {
            client_skt = skt.accept();
        } catch (...) {
            break;
        }
        int number = c_queue.current();
        clients.push_back(new PeerClient(number, std::move(client_skt), 
            &operations, stats));
        c_queue.next();
    }
}
void ClientListener::stop_listening() {
    skt.shutdown(SHUT_RDWR);
}

ClientListener::~ClientListener() {
    for (auto& client: clients) {
        client->join();
        delete client;
    }
}

