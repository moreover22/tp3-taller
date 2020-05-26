#ifndef SERVER_SOCKETSERVER_H
#define SERVER_SOCKETSERVER_H
#include "common_Socket.h"
#include <netdb.h>

struct SocketServerConf: public SocketConf {
    /**
     * @brief Se configura el socketopt para el bind.
     * @param fd file descritor asociado al socket.
     * @throw ConnectionError en caso de error.
     */
    void engage_bind_options(int fd) override;
    void engager(int sockfd, const struct sockaddr *addr, socklen_t addrlen) 
                                                                    override;

    SocketServerConf() {
        ai_flags = AI_PASSIVE;
        ai_family = AF_INET;
        ai_socktype = SOCK_STREAM;
    }
};

#endif
