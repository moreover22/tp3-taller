#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "common_Socket.h"
#include "common_Statistics.h"
#include "common_Thread.h"
#include "server_CircularQueue.h"
#include "server_SocketServerConf.h"
#include "server_ClientListener.h"


class Server: public Thread {
private:
    Socket socket;
    Statistics stat;
    SocketServerConf socket_server_conf;
    ClientListener listener;
    CircularQueue cq;
public:
    Server(const char* host, const char* number_path);
    void run() override;
    void show_statistics();
};
#endif
