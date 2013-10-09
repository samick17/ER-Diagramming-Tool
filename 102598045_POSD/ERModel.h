#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include "RelationShip.h"
#include "Connector.h"
#include "TableManager.h"

typedef pair<string,Component*> ComponentPair;

class ERModel{
public:
	ERModel();
	~ERModel();

	Component* addNode(string componentType);
	void addComponent(Component* component);
	void removeComponentByID(string id);
	int addConnection(Component* firstNode,Component* secondNode);
	Component* getComponentByID(string id);
	Connector* getNodesConnector(Component* firstNode,Component* secondNode);

	set<Component*> getAllComponents();
	set<Connector*> getAllConnectors();
	set<Entity*> getAllEntities();
	set<RelationShip*> getAllRelationShips();
	set<Table*> getAllTables();

	void clearComponentMap();

	vector<string> getComponentKeyOrderVector() const;
private:
	unordered_map<string,Component*> componentMap;
	vector<string> componentKeyOrderVector;
	void insertComponent(Component* component);
	void eraseComponent(Component* component);
	TableManager tableManager;
};