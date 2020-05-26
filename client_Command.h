#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#include <string>
#include "client_ClientComunication.h"
#include "common_NumberValidator.h"
#include "common_IInterchangeable.h"

class Command {
public:
    virtual void operator()(const std::string& input, ClientCommunication&
                                                        communication) = 0;
};

class NumberInputCommand: public Command {
private:
    NumberValidator validator;
public:
    void operator()(const std::string& input, ClientCommunication&
                                                        communication) override;
};

class SurrenderInputCommand: public Command {
public:
    void operator()(const std::string& input, ClientCommunication&
                                                        communication) override;
};

class HelpInputCommand: public Command {
public:
    void operator()(const std::string& input, ClientCommunication&
                                                        communication) override;
};

class DefaultInputCommand: public Command {
private:
    NumberValidator validator;
    NumberInputCommand number_command;
public:
    void operator()(const std::string& input, ClientCommunication&
                                                        communication) override;
};
#endif
