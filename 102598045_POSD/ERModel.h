#pragma once

#include "RelationShip.h"
#include "Connector.h"
#include "TableManager.h"
#include "HashMap.h"
#include "CommandManager.h"
#include "ISyncable.h"
#include "Subject.h"

class ERModel : public ISyncable,public Subject{
    friend class ERModelTest;
    FRIEND_TEST(ERModelTest,testAddNode);
    FRIEND_TEST(ERModelTest,testInsertComponent);
    FRIEND_TEST(ERModelTest,testEraseComponent);
    FRIEND_TEST(ERModelTest,testAddConnection);
    FRIEND_TEST(ERModelTest,testOpenFile);
    FRIEND_TEST(ERModelTest,testGetNodesConnector);
    FRIEND_TEST(ERModelTest,testGetAllComponents);
    FRIEND_TEST(ERModelTest,testGetAllConnectors);
    FRIEND_TEST(ERModelTest,testGetAllEntities);
    FRIEND_TEST(ERModelTest,testGetAllRelationShips);
    FRIEND_TEST(ERModelTest,testClearComponentMap);
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    FRIEND_TEST(CommandManagerTest,testRedoUndo);
    friend class IntegrationTest;
    FRIEND_TEST(IntegrationTest,testIsPrimaryExist);
    FRIEND_TEST(IntegrationTest,testUndoDeleteComponent);
    FRIEND_TEST(IntegrationTest,testRedoConnectComponent);
    FRIEND_TEST(IntegrationTest,testCommonUsage);
public:
    ERModel();
    ~ERModel();

    Node* addNode(string componentType);
    void insertComponent(Component* component);
    void insertComponentAt(Component* component,unsigned int index);
    void eraseComponent(Component* component);
    void deleteComponent(Component* component);
    int addConnection(Component* firstNode,Component* secondNode);
    void redo();
    void undo();
    void openFile(string filePath);
    void saveFile(string filePath);

    Component* getComponentByID(string id);
    Connector* getNodesConnector(Component* firstNode,Component* secondNode);
    HashMap<string,Component*>& getAllComponents();
    HashMap<string,Attribute*> getAllAttributes();
    HashMap<string,Entity*> getAllEntities();
    HashMap<string,RelationShip*> getAllRelationShips();
    HashMap<string,Connector*> getAllConnectors();
    HashMap<string,Table*> getAllTables();

    void clearComponentMap();
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(int syncEventType);
private:
    HashMap<string,Component*> componentMap;
    vector<ISynchronizer*> synchronizerVector;
    CommandManager commandManager;
    TableManager tableManager;
};