#include "common_Statistics.h"
#include <iostream>


void Statistics::count_loser() {
    std::lock_guard<std::mutex> lk(mtx);
    ++losers;
}

void Statistics::count_winner() {
    std::lock_guard<std::mutex> lk(mtx);
    ++winners;
}

void Statistics::show() {
    std::cout << "Estadísticas:\n";
    std::cout << "\tGanadores:  " << winners << "\n";
    std::cout << "\tPerdedores: " << losers << "\n";
}
