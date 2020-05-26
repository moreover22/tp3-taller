#include "client_InputCommand.h"
#include <string>

void InputCommand::push(const std::string& name, Command* command) {
    commands[name] = command;
}

void InputCommand::set_default(const std::string& name) {
    if (commands.count(name) == 0)
        throw std::out_of_range("Commando no reconocido: " + name);
    default_command = name;
}

Command* InputCommand::get(const std::string& name) const {
    if (commands.count(name) == 0) {
        return commands.at(default_command);
    }
    return commands.at(name);
}
