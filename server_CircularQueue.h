#ifndef SERVER_CIRCULARQUEUE_H
#define SERVER_CIRCULARQUEUE_H
#include <vector>
#include <cstddef>

class CircularQueue {
private:
    std::vector<int> elements;
    size_t index = 0;
public:
    void push(int i);
    int current() const;
    void next();
};
#endif
