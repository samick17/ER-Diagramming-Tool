#pragma once

#include "Command.h"
#include <gtest/gtest_prod.h> 

class ERModel;
class Component;
class Connector;

class ConnectNodeCommand : public Command{
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    friend class ConnectNodeCommandTest;
    FRIEND_TEST(ConnectNodeCommandTest,testConnectNodeCommand);
    FRIEND_TEST(ConnectNodeCommandTest,testBackupConnector);
public:
    ConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector);
    ~ConnectNodeCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    ERModel* erModel;
    Component* firstNode;
    Component* secondNode;
    Connector* connector;
};