#include "server_PeerClient.h"
#include <cstring>
#include <netinet/in.h>
#include <map>
#include <string>
#include "server_Operation.h"


#define LOSE_CLIENT_MSG ("Perdiste")
#define WIN_CLIENT_MSG ("Ganaste")
#define SIZEOF_UINT16 2
#define SIZEOF_BYTE 1

PeerClient::PeerClient(int number, Socket client, std::map<char, Operation*>* 
    operations, Statistics& stats): number(number), client(std::move(client)), 
                operations(operations), tries(0), _is_open(true), stats(stats){
    start();
}

int PeerClient::send(const char* buffer, size_t len) {
    return client.send(buffer, len);
}

int PeerClient::receive(char* buffer, size_t len) {
    return client.receive(buffer, len);
}

bool PeerClient::verify_number(const int& number) const {
    return this->number == number;
}

bool PeerClient::validate_tries() const {
    return tries < MAX_TRIES;
}

void PeerClient::count_try() {
    ++tries;
}

void PeerClient::lose() {
    uint16_t len_msg = strlen(LOSE_CLIENT_MSG);
    uint16_t len_be = htons(len_msg);
    send((char *) &len_be, SIZEOF_UINT16);
    send(LOSE_CLIENT_MSG, len_msg);
    _is_open = false;
    stats.count_loser();
}

void PeerClient::win() {
    uint16_t len_msg = strlen(WIN_CLIENT_MSG);
    uint16_t len_be = htons(len_msg);
    send((char *) &len_be, SIZEOF_UINT16);
    send(WIN_CLIENT_MSG, len_msg);
    _is_open = false;
    stats.count_winner();
}

bool PeerClient::is_open() {
    return _is_open;
}

void PeerClient::count_corrections(std::map<Correction, size_t>& 
                                correction_count, const std::string& guess) {
    std::string number_as_string = std::to_string(number);
    for (size_t i = 0; i < guess.length(); ++i) {
        if (number_as_string[i] == guess[i]) {
            correction_count[Correction::right]++;
            continue;
        }
        if (number_as_string.find(guess[i]) != std::string::npos) {
            correction_count[Correction::regular]++;
            continue;
        }
        correction_count[Correction::wrong]++;
    }
}


void PeerClient::run() {
    char operation;
    while (is_open()) {
        receive(&operation, SIZEOF_BYTE);
        (*operations->at(operation))(*this);
    }
}
