#include "client_SocketClientConf.h"


void SocketClientConf::engage_bind_options(int fd) {}

bool SocketClientConf::engager(int sockfd, const struct sockaddr *addr, 
                                                        socklen_t addrlen) {
    int status = ::connect(sockfd, addr, addrlen);
    return status != -1;
}
