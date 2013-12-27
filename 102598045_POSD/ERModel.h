#pragma once

#include "RelationShip.h"
#include "Connector.h"
#include "TableManager.h"
#include "HashMap.h"
#include "CommandManager.h"
#include "ISyncable.h"
#include "Cardinality.h"
#include "Subject.h"
#include "ClipBoard.h"

class ClipBoardState;

class ERModel : public ISyncable,public Subject{
    friend class ERModelTest;
    FRIEND_TEST(ERModelTest,testAddNode);
    FRIEND_TEST(ERModelTest,testAddConnection);
    FRIEND_TEST(ERModelTest,testOpenFile);
    FRIEND_TEST(ERModelTest,testGetNodesConnector);
    FRIEND_TEST(ERModelTest,testGetAllComponents);
    FRIEND_TEST(ERModelTest,testGetAllAttributes);
    FRIEND_TEST(ERModelTest,testGetAllEntities);
    FRIEND_TEST(ERModelTest,testGetAllRelationShips);
    FRIEND_TEST(ERModelTest,testGetAllConnectors);
    FRIEND_TEST(ERModelTest,testResetERModel);
    FRIEND_TEST(ERModelTest,testIsPrimaryExist);
    FRIEND_TEST(ERModelTest,testUndoDeleteComponent);
    FRIEND_TEST(ERModelTest,testRedoConnectComponent);
    FRIEND_TEST(ERModelTest,testCommonUsage);
    friend class CommandManagerTest;
    FRIEND_TEST(CommandManagerTest,testCommandManager);
    FRIEND_TEST(CommandManagerTest,testRedoUndo);
    FRIEND_TEST(CommandManagerTest,testPopAllStack);
    friend class AddNodeCommandTest;
    FRIEND_TEST(AddNodeCommandTest,testExecute);
    FRIEND_TEST(AddNodeCommandTest,testUnexecute);
    FRIEND_TEST(AddNodeCommandTest,testAddNodeCommand);
    friend class ConnectNodeCommandTest;
    FRIEND_TEST(ConnectNodeCommandTest,testExecute);
    FRIEND_TEST(ConnectNodeCommandTest,testUnexecute);
    FRIEND_TEST(ConnectNodeCommandTest,testConnectNodeCommand);
    friend class DeleteComponentCommandTest;
    FRIEND_TEST(DeleteComponentCommandTest,testExecute);
    FRIEND_TEST(DeleteComponentCommandTest,testUnexecute);
    FRIEND_TEST(DeleteComponentCommandTest,testDeleteComponentCommand);
    FRIEND_TEST(DeleteComponentCommandTest,testSaveConnectionData);
    FRIEND_TEST(DeleteComponentCommandTest,testClearConnectionDataMap);
    FRIEND_TEST(DeleteComponentCommandTest,testRemoveAndDisconnectComponents);
    FRIEND_TEST(DeleteComponentCommandTest,testReConnectComponents);
public:
    ERModel();
    ~ERModel();

    Node* addNode(string nodeType);
    void deleteComponent(vector<string> componentIDVector);
    int addConnection(Component* firstNode,Component* secondNode);
    bool canUndo();
    bool canRedo();
    void undo();
    void redo();
    void setPrimaryKey(string componentID);
    bool setCardinality(Connector* connector,string cardinality);
    void setComponentText(string componentID,string text);
    void moveComponents(vector<string> selectedComponentsIDVector,Point mousePressPosition,Point mouseReleasePosition);
    void openFile(string filePath);
    void saveFile(string filePath);
    //clip board related
    bool canPaste();
    void cutComponents(vector<string> componentIDVector);
    void copyComponents(vector<string> componentIDVector);
    void pasteComponents();

    Component* getComponentByID(string id);
    Connector* getNodesConnector(Component* firstNode,Component* secondNode);
    Cardinality* getCardinality();
    HashMap<string,Component*> getAllComponents();
    HashMap<string,Attribute*> getAllAttributes();
    HashMap<string,Entity*> getAllEntities();
    HashMap<string,RelationShip*> getAllRelationShips();
    HashMap<string,Connector*> getAllConnectors();
    HashMap<string,Table*> getAllTables();

    void resetERModel();
    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);
private:
    void initialCountMap();
    void resetCounting();
    void setNodePosition(string componentType,Node* node);
    void switchClipBoardState(int clipBoardStateID);
    void deleteClipBoardState();
    HashMap<string,Component*> getComponentsByIDVector(vector<string> componentIDVector);
    int attributeCount,entityCount,relationShipCount;
    ClipBoard clipBoard;
    ClipBoardState* clipBoardState;
    HashMap<string,int*> componentTypeCountMap;
    HashMap<string,Component*> componentMap;
    HashMap<string,Component*> clonedComponentMap;
    Cardinality cardinality;
    vector<ISynchronizer*> synchronizerVector;
    unordered_map<string,double> componentTypeMapOffsetX;
    CommandManager commandManager;
    TableManager tableManager;
};