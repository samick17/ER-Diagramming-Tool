#pragma once

#include "Command.h"
#include "Node.h"
#include "Connector.h"

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