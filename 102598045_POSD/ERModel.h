#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include "RelationShip.h"
#include "Connector.h"
#include "TableManager.h"
#include <gtest/gtest_prod.h> 

typedef pair<string,Component*> ComponentPair;

class ERModel{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest,addNode);
	FRIEND_TEST(ERModelTest,insertComponent);
	FRIEND_TEST(ERModelTest,eraseComponent);	
	FRIEND_TEST(ERModelTest,addConnection);
	FRIEND_TEST(ERModelTest,getNodesConnector);
	FRIEND_TEST(ERModelTest,getAllComponents);
	FRIEND_TEST(ERModelTest,getAllConnectors);
	FRIEND_TEST(ERModelTest,getAllEntities);
	FRIEND_TEST(ERModelTest,getAllRelationShips);
	FRIEND_TEST(ERModelTest,clearComponentMap);
public:	
	ERModel();
	~ERModel();

	Component* addNode(string componentType);
	void insertComponent(Component* component);
	void eraseComponent(Component* component);
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
	TableManager tableManager;
};