#pragma once

#include "Command.h"
#include <stack>
#include <gtest/gtest_prod.h>

class ERModel;
class TextUI;
class Command;
class Presentation;

using namespace std;

class CommandManager{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testPopAllStack);
public:
    CommandManager();
    ~CommandManager();

    void execute(Command* command);
    void undo();
    void redo();

    void popAllStack();
private:
    stack<Command*> redoCommandsStack;
    stack<Command*> undoCommandsStack;
};