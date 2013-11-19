#pragma once

#include "Command.h"
#include "Connector.h"
#include "ConnectionData.h"
#include "HashMap.h"

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
    ERModel* erModel;
    Component* component;
    HashMap<string,Connector*> connectionMap;
    HashMap<string,ConnectionData*> connectionDataMap;
    HashMap<string,unsigned int> componentIndexMap;
    void saveConnectionData(Connector* connector);
    void clearConnectionDataMap();
    void removeAndDisconnectComponents();
    void reConnectComponents(ConnectionData* connectionData,Connector* connector);
};