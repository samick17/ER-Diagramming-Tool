#pragma once

#include "Command.h"
#include "ConnectionData.h"
#include "HashMap.h"
#include <gtest/gtest_prod.h> 

class ERModel;
class Component;
class Connector;

class DeleteComponentCommand : public Command{
    friend class DeleteComponentCommandTest;
    FRIEND_TEST(DeleteComponentCommandTest,testDeleteComponentCommand);
    FRIEND_TEST(DeleteComponentCommandTest,testSaveConnectionData);
    FRIEND_TEST(DeleteComponentCommandTest,testClearConnectionDataMap);
    FRIEND_TEST(DeleteComponentCommandTest,testRemoveAndDisconnectComponents);
    FRIEND_TEST(DeleteComponentCommandTest,testReConnectComponents);
public:
    DeleteComponentCommand(ERModel* erModel,Component* component);
    ~DeleteComponentCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    void saveConnectionData(Connector* connector);
    void clearConnectionDataMap();
    void removeAndDisconnectComponents();
    void reConnectComponents(ConnectionData* connectionData,Connector* connector);
    ERModel* erModel;
    Component* component;
    HashMap<string,Connector*> connectionMap;
    HashMap<string,ConnectionData*> connectionDataMap;
    HashMap<string,unsigned int> componentIndexMap;
};