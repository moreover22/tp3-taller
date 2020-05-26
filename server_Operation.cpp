#include "server_Operation.h"
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <utility>

#define HELP_CLIENT_MSG "" \
"Comandos válidos:\n" \
"\tAYUDA: despliega la lista de comandos válidos\n" \
"\tRENDIRSE: pierde el juego automáticamente\n" \
"\tXXX: Número de 3 cifras a ser enviado al servidor para adivinar el número " \
"secreto"

#define SIZEOF_UINT16 2

void OperationHelp::operator()(PeerClient& peer_client) {
    uint16_t len_msg = strlen(HELP_CLIENT_MSG);
    uint16_t len_be = htons(len_msg);
    peer_client.send((char *) &len_be, SIZEOF_UINT16);
    peer_client.send(HELP_CLIENT_MSG, len_msg);
}

void OperationSurrender::operator()(PeerClient& peer_client) {
    peer_client.lose();
}

std::string correction_message(std::map<Correction, size_t>& 
                                                            correction_count) {
    if (correction_count[Correction::right] == 0 && 
        correction_count[Correction::regular] == 0){
        return std::move(std::string("3 mal"));
    }
    if (correction_count[Correction::regular] == 0) {
        size_t right_count = correction_count[Correction::right];
        std::string right_count_s = std::to_string(right_count);
        return std::move(std::string(right_count_s + " bien"));
    }
    if (correction_count[Correction::right] == 0) {
        size_t regular_count = correction_count[Correction::regular];
        std::string regular_count_s = std::to_string(regular_count);
        return std::move(std::string(regular_count_s + " regular"));
    }
    size_t right_count = correction_count[Correction::right];
    std::string right_count_s = std::to_string(right_count);
    size_t regular_count = correction_count[Correction::regular];
    std::string regular_count_s = std::to_string(regular_count);
    std::stringstream correction_s;
    correction_s << right_count_s.c_str() << " bien, " << 
                                        regular_count_s.c_str() << " regular";
    return std::move(correction_s.str());
}

void OperationCheckNumber::operator()(PeerClient& peer_client) {
    uint16_t guess_number;
    peer_client.receive((char *) &guess_number, SIZEOF_UINT16);
    guess_number = ntohs(guess_number);
    std::string guess_s = std::to_string(guess_number);;

    std::map<Correction, size_t> correction_count{
        { Correction::regular, 0 },
        { Correction::right, 0 },
        { Correction::wrong, 0 }
    };
    peer_client.count_corrections(correction_count, guess_s);
    std::string correction = correction_message(correction_count);
    peer_client.count_try();
    if (peer_client.verify_number(guess_number)) {
        peer_client.win();
    } else if (!peer_client.validate_tries()) {
        peer_client.lose();
    } else {
        uint16_t len_msg = correction.length();
        uint16_t len_be = htons(len_msg);
        peer_client.send((char *) &len_be, SIZEOF_UINT16);
        peer_client.send(correction.c_str(), len_msg);
    }
}
