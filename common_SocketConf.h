#ifndef COMMON_SOCKETCONF_H
#define COMMON_SOCKETCONF_H

#include <sys/socket.h>

struct SocketConf {
    /**
     * @brief Se configura el socketopt para el bind.
     * @param fd file descritor asociado al socket.
     * @throw ConnectionError en caso de error.
     */
    virtual void engage_bind_options(int fd) = 0;
    virtual bool engager(int sockfd, const struct sockaddr *addr, 
                                                        socklen_t addrlen) = 0;
    int ai_flags;
    int ai_family;
    int ai_socktype;
};
#endif
