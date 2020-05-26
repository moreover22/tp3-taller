#include "common_SocketClientConf.h"
#define _POSIX_C_SOURCE 200809L

#include "common_Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "common_ConnectionError.h"

#define SKT_ERROR -1
#define ERROR -1
#define SUCCESS 0
#define LISTEN_BACKLOG 10

#define INVALID_FD -1


static ssize_t _interchanger_send(int sockfd, char *buf, size_t len);
static ssize_t _interchanger_receive(int sockfd, char *buf, size_t len);


Socket::~Socket() {
    if (file_descriptor == INVALID_FD)
        return;
    this->shutdown(SHUT_RDWR);
    ::close(file_descriptor);
}

void Socket::shutdown(int how) {
    if (file_descriptor == INVALID_FD)
        return;
    ::shutdown(file_descriptor, how);
}

int Socket::send(const char *mensaje, size_t length) {
    interchanger = _interchanger_send;
    return interchange_data((char *) mensaje, length);
}

int Socket::receive(char *buf, size_t length) {
    interchanger = _interchanger_receive;
    return interchange_data( buf, length);
}

void Socket::connect(const char *host, const char *service) {
    engage_service(host, service);
}

void Socket::bind_and_listen(const char *service) {
    engage_service((const char *)INADDR_ANY, service);
    if (::listen(file_descriptor, LISTEN_BACKLOG) != SUCCESS) {
        throw ConnectionError("Error: socket listen");
    }
}

Socket Socket::accept(SocketConf& conf) {
    int peerskt = ::accept(file_descriptor, NULL, NULL);
    if (peerskt == -1)
        throw ConnectionError("Error: en socket accept");
    Socket client(conf);
    client.file_descriptor = peerskt;
    return client;
}

void Socket::resolve_addrinfo(const char *host, 
                                    const char *service, addrinfo_t **result) {
    addrinfo_t hints;
    memset(&hints, 0, sizeof(addrinfo_t)); 
    hints.ai_family = configuration.ai_family;
    hints.ai_socktype = configuration.ai_socktype;
    hints.ai_flags = configuration.ai_flags;
    int status = getaddrinfo(host, service, &hints, result);
    if (status == -1) {
        throw ConnectionError("Error en getaddrinfo: %s\n", 
                                                        gai_strerror(status));
    }
}


int Socket::engage_host(addrinfo_t *host_info) {
    addrinfo_t *hi = host_info;
    int fd = socket(hi->ai_family, hi->ai_socktype, hi->ai_protocol);
    if (fd == SKT_ERROR) {
        throw ConnectionError("Error socket: %s\n", strerror(errno));
    }
    configuration.engage_bind_options(fd);
    configuration.engager(fd, hi->ai_addr, hi->ai_addrlen);
    file_descriptor = fd;
    return SUCCESS;
}

bool Socket::multiple_engage(addrinfo_t *hosts) {
    addrinfo_t *ptr = hosts;
    bool is_engaged = false;
    while (ptr != NULL && !is_engaged) {
        is_engaged = (engage_host(ptr) == SUCCESS);
        ptr = ptr->ai_next;
    }
    return is_engaged;
}

void Socket::engage_service(const char *host, const char *service) {
    addrinfo_t *result;
    resolve_addrinfo(host, service, &result);
    bool is_engaged = multiple_engage(result);
    freeaddrinfo(result);
    if (!is_engaged) {
        throw ConnectionError("Error. No se pudo conectar.\n");
    }
}

int Socket::interchange_data(char *buf, size_t length) {
    ssize_t bytes_interchanged = 0;
    ssize_t total = 0;
    ssize_t restantes = length;
    int fd = file_descriptor;
    while (restantes > 0) {
        bytes_interchanged = interchanger(fd, &buf[total], restantes);
        if (bytes_interchanged ==  0) {
            break;
        } else if (bytes_interchanged < 0) {
            throw ConnectionError("Error sending data: %s\n", strerror(errno));
        }
        total += bytes_interchanged;
        restantes = length - bytes_interchanged;
    }
    return total;
}

Socket::Socket(Socket&& other): configuration(other.configuration) {
    this->file_descriptor = other.file_descriptor;
    other.file_descriptor = INVALID_FD;
}

Socket& Socket::operator=(Socket&& other) {
    this->file_descriptor = other.file_descriptor;
    this->configuration = other.configuration;
    other.file_descriptor = INVALID_FD;
    return *this;
}

static ssize_t _interchanger_send(int sockfd, char *buf, size_t len) {
    return send(sockfd, buf, len, MSG_NOSIGNAL);
}

static ssize_t _interchanger_receive(int sockfd, char *buf, size_t len) {
    return recv(sockfd, buf, len, 0);
}
