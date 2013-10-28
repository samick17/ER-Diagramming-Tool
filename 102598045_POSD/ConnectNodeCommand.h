#pragma once

#include "Command.h"
#include "Node.h"
#include "Connector.h"

class ConnectNodeCommand : public Command{
    friend class IntegrationTest;
    FRIEND_TEST(IntegrationTest,testRedoConnectComponent);
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    friend class ConnectNodeCommandTest;
    FRIEND_TEST(ConnectNodeCommandTest,testConnectNodeCommand);
    FRIEND_TEST(ConnectNodeCommandTest,testBackupConnector);
public:
    ConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector);
    ~ConnectNodeCommand();

    void execute();
    void unExecute();
private:
	ERModel* erModel;
    Component* firstNode;
    Component* secondNode;
    Connector* connector;
};