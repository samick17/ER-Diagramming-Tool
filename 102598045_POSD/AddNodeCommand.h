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
protected:
    void onUnExecuteDestroy();
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    Component* node;
};