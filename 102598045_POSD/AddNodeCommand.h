#pragma once

#include "Command.h"
#include "HashMap.h"
#include <gtest/gtest_prod.h> 

class Component;
class Node;

class AddNodeCommand : public Command{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    friend class AddNodeCommandTest;
    FRIEND_TEST(AddNodeCommandTest,testAddNodeCommand);
public:
    AddNodeCommand(HashMap<string,Component*>& componentMap,Node* node);
    ~AddNodeCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    HashMap<string,Component*>& componentMap;
    Node* node;
};