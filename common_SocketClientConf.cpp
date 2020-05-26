#include "common_SocketClientConf.h"
#include "common_ConnectionError.h"


void SocketClientConf::engage_bind_options(int fd) {}

void SocketClientConf::engager(int sockfd, const struct sockaddr *addr, 
                                                        socklen_t addrlen) {
    int status = ::connect(sockfd, addr, addrlen);
    if (status == -1) {
        throw ConnectionError("Error: connect client socket");
    }
}
