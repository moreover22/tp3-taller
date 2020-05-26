#ifndef CLIENT_INPUTCOMMAND_H
#define CLIENT_INPUTCOMMAND_H

#include <map>
#include <string>
#include "client_Command.h"

class InputCommand {
private:
    std::map<std::string, Command *> commands;
    std::string default_command;
public:
    void push(const std::string& name, Command* command);
    void set_default(const std::string& name);
    Command* get(const std::string& name) const;
};

#endif
