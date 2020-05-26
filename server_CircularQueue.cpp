#include "server_CircularQueue.h"

void CircularQueue::push(int i) {
    this->elements.push_back(i);    
}

int CircularQueue::current() const {
    return this->elements.at(index);
}

void CircularQueue::next() {
    this->index++;
    if (index == elements.size())
        index = 0;
}
