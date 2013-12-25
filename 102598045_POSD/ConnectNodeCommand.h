#pragma once

#include "Command.h"
#include "HashMap.h"
#include <gtest/gtest_prod.h> 

class Component;
class Connector;

class ConnectNodeCommand : public Command{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    friend class ConnectNodeCommandTest;
    FRIEND_TEST(ConnectNodeCommandTest,testExecute);
    FRIEND_TEST(ConnectNodeCommandTest,testConnectNodeCommand);
    FRIEND_TEST(ConnectNodeCommandTest,testUnexecute);
    FRIEND_TEST(ConnectNodeCommandTest,testBackupConnector);
public:
    ConnectNodeCommand(HashMap<string,Component*>& componentMap,Component* firstNode,Component* secondNode,Connector* connector);
    ~ConnectNodeCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    HashMap<string,Component*>& componentMap;
    Component* firstNode;
    Component* secondNode;
    Connector* connector;
};