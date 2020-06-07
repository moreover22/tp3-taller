#ifndef CLIENT_SOCKETCLIENTCONF_H
#define CLIENT_SOCKETCLIENTCONF_H

#include "common_SocketConf.h"
#include <sys/socket.h>

struct SocketClientConf: public SocketConf {
    /**
     * @brief Se configura el socketopt para el bind.
     * @param fd file descritor asociado al socket.
     * @throw ConnectionError en caso de error.
     */
    void engage_bind_options(int fd) override;
    bool engager(int sockfd, const struct sockaddr *addr, socklen_t addrlen) 
                                                                    override;
    SocketClientConf() {
        ai_flags = AF_UNSPEC;
        ai_family = AF_INET;
        ai_socktype = SOCK_STREAM;
    }
};

#endif
