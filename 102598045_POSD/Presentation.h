#pragma once

#include <string>
#include "HashMap.h"
#include "IObserver.h"

class Component;
class Node;
class Attribute;
class Entity;
class RelationShip;
class Connector;
class Table;
class ERModel;

using namespace std;

class Presentation{
public:
    Presentation(ERModel* erModel);
    virtual ~Presentation();

    void openFile(string filePath);
    void saveFile(string filePath);
    void close();

    Node* addNode(string componentType);
    void deleteComponent(Component* component);
    int addConnection(Component* firstNode,Component* secondNode);
    void redo();
    void undo();

    Component* getComponentByID(string id);
    Connector* getNodesConnector(Component* firstNode,Component* secondNode);
    HashMap<string,Component*> getAllComponents();
    HashMap<string,Attribute*> getAllAttributes();
    HashMap<string,Entity*> getAllEntities();
    HashMap<string,RelationShip*> getAllRelationShips();
    HashMap<string,Connector*> getAllConnectors();
    HashMap<string,Table*> getAllTables();

    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify(int notifiedEventType);
    void notify(IObserver* observer,int notifiedEventType);
private:
    ERModel* erModel;
};