#ifndef COMMON_NUMBERPARSER_H
#define COMMON_NUMBERPARSER_H

#include <fstream>
#include <string>
#include "common_NumberValidator.h"
#include "server_CircularQueue.h"

#define ERROR_INVALID_INPUT "Error: archivo con entrada inválida"
#define ERROR_OUT_OF_RANGE "Error: archivo con números fuera de rango"
#define ERROR_INVALID_FORMAT "Error: formato de los números inválidos"
#define ERROR_CANT_OPEN_FILE "Error: no se pudo abrir el archivo."

class NumberParser {
private:
    NumberValidator validator;
    std::fstream stream;
    void validate_line(const std::string& line);
public:
    explicit NumberParser(const char* path);
    void parse(CircularQueue& cq);
};
#endif
