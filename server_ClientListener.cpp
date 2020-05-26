#include "server_ClientListener.h"
#include "common_SocketClientConf.h"
#include "server_Operation.h"
#include <map>
#include <utility>

void ClientListener::listen() {
    OperationHelp help_operation;
    OperationSurrender surrender_operation;
    OperationCheckNumber check_number_operation;
    std::map<char, Operation*> operations{
        {'h', &help_operation},
        {'s', &surrender_operation},
        {'n', &check_number_operation}
    };
    SocketClientConf socket_client_conf;
    while (true) {
        Socket client_skt(socket_client_conf);
        try {
            client_skt = skt.accept(socket_client_conf);
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

