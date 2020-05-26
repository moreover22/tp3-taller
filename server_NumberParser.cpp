#include <exception>
#include <string>
#include "server_NumberParser.h"

NumberParser::NumberParser(const char* path) {
    stream = std::fstream(path, std::ios::in);
    if (!stream.is_open())
        throw std::invalid_argument(ERROR_CANT_OPEN_FILE);
}


void NumberParser::validate_line(const std::string& line) {
    if (!validator.is_numeric(line))
        throw std::invalid_argument(ERROR_INVALID_INPUT);
    if (!validator.validate_range(line))
        throw std::invalid_argument(ERROR_OUT_OF_RANGE);
    if (!validator.validate_unique_digit(line))
        throw std::invalid_argument(ERROR_INVALID_FORMAT);
}

void NumberParser::parse(CircularQueue& cq) {
    while (!stream.eof()) {
        std::string line;
        std::getline(stream, line);
        if (line.empty()) continue;
        validate_line(line);
        cq.push(std::stoi(line));
    }
}
