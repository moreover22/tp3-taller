#ifndef COMMON_NUMBERVALIDATOR_H
#define COMMON_NUMBERVALIDATOR_H
#include <string>

class NumberValidator {
private:
    const short MIN = 100;
    const short MAX = 999;
public:
    bool validate_range(const std::string& input) const;
    bool validate_unique_digit(const std::string& input) const;
    bool validate(const std::string& input) const;
    bool is_numeric(const std::string& input) const;
    bool validate_range(const std::string& input, int min, int max) const;
};


#endif
