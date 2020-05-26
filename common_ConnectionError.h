#ifndef COMMON_CONNECTIONERR_H
#define COMMON_CONNECTIONERR_H
#include <exception>
#define ERROR_MSG_LEN 256

class ConnectionError: public std::exception {
private:
    char error_msg[ERROR_MSG_LEN];
public:
    explicit ConnectionError(const char* format, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~ConnectionError() noexcept {}
};
#endif
