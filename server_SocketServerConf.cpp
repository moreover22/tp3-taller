#include "server_SocketServerConf.h"
#include "common_ConnectionError.h"


void SocketServerConf::engage_bind_options(int fd) {
    int val = 1;
    int s = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (s != 0) {
        throw ConnectionError("Error: setsockopt del socket server.");
    }
}

bool SocketServerConf::engager(int sockfd, const struct sockaddr *addr, 
                                                        socklen_t addrlen) {
    int status = ::bind(sockfd, addr, addrlen);
    return status != -1;
}
