#ifndef SERVER_STATISTICS_H
#define SERVER_STATISTICS_H

#include <mutex>
#include <cstddef>
class Statistics {
private:
    size_t winners = 0;
    size_t losers = 0;
    std::mutex mtx;
public:
    void count_winner();
    void count_loser();
    void show();
};
#endif
