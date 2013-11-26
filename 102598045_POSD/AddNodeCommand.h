#pragma once

#include "Command.h"
#include <gtest/gtest_prod.h> 

class ERModel;
class Node;

class AddNodeCommand : public Command{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    friend class AddNodeCommandTest;
    FRIEND_TEST(AddNodeCommandTest,testAddNodeCommand);
public:
    AddNodeCommand(ERModel* erModel,Node* node);
    ~AddNodeCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    Node* node;
};