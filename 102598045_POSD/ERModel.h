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
	FRIEND_TEST(ERModelTest,testAddNode);
	FRIEND_TEST(ERModelTest,testInsertComponent);
	FRIEND_TEST(ERModelTest,testEraseComponent);	
	FRIEND_TEST(ERModelTest,testAddConnection);
	FRIEND_TEST(ERModelTest,testGetNodesConnector);
	FRIEND_TEST(ERModelTest,testGetAllComponents);
	FRIEND_TEST(ERModelTest,testGetAllConnectors);
	FRIEND_TEST(ERModelTest,testGetAllEntities);
	FRIEND_TEST(ERModelTest,testGetAllRelationShips);
	FRIEND_TEST(ERModelTest,testClearComponentMap);
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
	unordered_map<string,Table*> getAllTables();

	void clearComponentMap();

	vector<string> getComponentKeyOrderVector() const;
private:
	unordered_map<string,Component*> componentMap;
	vector<string> componentKeyOrderVector;	
	TableManager tableManager;
};