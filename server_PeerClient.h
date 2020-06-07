#ifndef SERVER_PEERCLIENT_H
#define SERVER_PEERCLIENT_H
#include "common_IInterchangeable.h"
#include "common_Socket.h"
#include "common_Thread.h"
#include "server_Statistics.h"
#include <utility>
#include <map>
#include <string>
class Operation;

enum class Correction { wrong, right, regular };

class PeerClient: public Thread, public IInterchangeable {
private:
    const static int MAX_TRIES = 10;
    int number;
    Socket client;
    std::map<char, Operation*>* operations;
    int tries;
    bool _is_open;
    Statistics& stats;

public:
    PeerClient(int number, Socket client, std::map<char, Operation*>* 
    operations, Statistics& stats);
    int send(const char* buffer, size_t len) override;
    int receive(char* buffer, size_t len) override;
    bool verify_number(const int& number) const;
    bool validate_tries() const;
    void count_try();
    void lose();
    void win();
    bool is_open();
    void count_corrections(std::map<Correction, size_t>& correction_count,
                                                    const std::string& guess);
    void run() override;
};
#endif
