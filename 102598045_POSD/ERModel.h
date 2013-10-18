#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include "RelationShip.h"
#include "Connector.h"
#include "TableManager.h"
#include "HashMap.h"

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

	HashMap<string,Component*> getAllComponents();
	HashMap<string,Connector*> getAllConnectors();
	HashMap<string,Entity*> getAllEntities();
	HashMap<string,RelationShip*> getAllRelationShips();
	HashMap<string,Table*> getAllTables();

	void clearComponentMap();
private:
	HashMap<string,Component*> componentMap;
	TableManager tableManager;
};