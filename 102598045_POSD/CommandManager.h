#pragma once

#include "Command.h"
#include <stack>

class ERModel;
class TextUI;
class Command;
class Presentation;

class CommandManager{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testPopAllStack);
public:
    CommandManager();
    ~CommandManager();

    void execute(Command* command);
    void redo();
    void undo();

    void popAllStack();
private:
    stack<Command*> redoCommandsStack;
    stack<Command*> undoCommandsStack;
};