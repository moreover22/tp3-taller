#include "common_ConnectionError.h"

#include <errno.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>


ConnectionError::ConnectionError(const char *format, ...) noexcept {
    auto _errno = errno;
    va_list args;
    va_start(args, format);
    int s = vsnprintf(error_msg, ERROR_MSG_LEN, format, args);
    va_end(args);
    strncpy(error_msg + s, strerror(_errno), ERROR_MSG_LEN - s);
    error_msg[ERROR_MSG_LEN - 1] = 0;
}

const char* ConnectionError::what() const noexcept {
    return error_msg;
}
