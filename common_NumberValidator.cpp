#include "common_NumberValidator.h"
#include <algorithm>
#include <unordered_set>
#include <string>

#define MAX_NUMBER_LEN 5

bool NumberValidator::validate(const std::string& input) const {
    if (!validate_range(input)) {
        return false;
    }
    if (!validate_unique_digit(input)) {
        return false;
    }
    return true;
}

bool NumberValidator::is_numeric(const std::string& input) const {
    size_t digit_count = std::count_if(input.begin(), input.end(), 
        [](const char c) -> bool {
            return std::isdigit(c);
        });
    return digit_count == input.size();
}

bool NumberValidator::validate_range(const std::string& input) const { 
    return validate_range(input, MIN, MAX);
}

bool NumberValidator::validate_range(const std::string& input, int min, 
                                                                int max) const {
    if (input.length() > MAX_NUMBER_LEN || !is_numeric(input))
        return false;
    int number = std::stoi(input);
    return number >= min && number <= max;
}

bool NumberValidator::validate_unique_digit(const std::string& input) const {
    std::unordered_set<char> digits;
    for (const auto& c: input) {
        if (digits.count(c) != 0)
            return false;
        digits.insert(c);
    }
    return true;
}
