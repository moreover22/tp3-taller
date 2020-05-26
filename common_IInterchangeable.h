#ifndef COMMON_IINTERCHANGEABLE_H
#define COMMON_IINTERCHANGEABLE_H
#include <cstddef>

class ISendable {
public:
    virtual int send(const char* buffer, size_t len) = 0;
};

class IReceivable {
public:
    virtual int receive(char* buffer, size_t len) = 0;
};

class IInterchangeable: public ISendable, public IReceivable {
};
#endif
