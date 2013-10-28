#pragma once

#include "Command.h"

class AddNodeCommand : public Command{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    friend class AddNodeCommandTest;
    FRIEND_TEST(AddNodeCommandTest,testAddNodeCommand);
public:
    AddNodeCommand(ERModel* erModel,Node* node);
    ~AddNodeCommand();

    void execute();
    void unExecute();
private:    
    ERModel* erModel;
    Component* node;
};