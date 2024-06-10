#pragma once

#include <stack>
#include "Command.h"

class CommandManager {
private:
    std::stack<Command*> commandHistory;

public:
    void ExecuteCommand(Command* command) {
        command->Execute();
        commandHistory.push(command);
    }

    void Undo() {
        if (!commandHistory.empty()) {
            Command* command = commandHistory.top();
            commandHistory.pop();
            command->Undo();
            delete command;
        }
    }

    ~CommandManager() {
        while (!commandHistory.empty()) {
            delete commandHistory.top();
            commandHistory.pop();
        }
    }
};
