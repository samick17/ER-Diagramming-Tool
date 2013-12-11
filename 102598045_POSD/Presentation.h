#pragma once

#include <string>
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
    void deleteComponent(string componentID);
    int addConnection(Component* firstNode,Component* secondNode);
    void redo();
    void undo();
    bool setCardinality(Connector* connector,string cardinality);
    void setPrimaryKey(string componentID);
    void setComponentText(string componentID,string text);

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

    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);
private:
    ERModel* erModel;
};