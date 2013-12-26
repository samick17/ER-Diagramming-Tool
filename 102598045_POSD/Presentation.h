#pragma once

#include <string>
#include <vector>
#include "Point.h"
#include "HashMap.h"
#include "ISynchronizer.h"

class Component;
class Node;
class Attribute;
class Entity;
class RelationShip;
class Connector;
class Table;
class ERModel;
class IObserver;
class Cardinality;

using namespace std;

class Presentation{
public:
    Presentation(ERModel* erModel);
    virtual ~Presentation();

    void openFile(string filePath);
    void saveFile(string filePath);
    void close();

    Node* addNode(string nodeType);
    void deleteComponent(vector<string> componentIDVector);
    int addConnection(Component* firstNode,Component* secondNode);
    bool canRedo();
    bool canUndo();
    void redo();
    void undo();
    bool setCardinality(Connector* connector,string cardinality);
    void setPrimaryKey(string componentID);
    void setComponentText(string componentID,string text);
    void moveComponents(vector<string> selectedComponentsIDVector,Point mousePressPosition,Point mouseReleasePosition);
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

    void registerSynchronizer(ISynchronizer* synchronizer);
    void unregisterSynchronizer(ISynchronizer* synchronizer);
    void sync(string syncEventType);

    void registerObserverToModel(IObserver* observer);
    void unregisterObserverToModel(IObserver* observer);
    void notifyModel();
private:
    ERModel* erModel;
};