#pragma once
#include "Entity.h"
#include "Attribute.h"
#include <set>
#include <string>
#include "HashMap.h"

class Table{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest,testGetAllTables);
	friend class IntegrationTest;
	FRIEND_TEST(IntegrationTest,testIsPrimaryExist);
public:	
	Table(Entity* entity);
	~Table();
	
	void insertAllAttributes(HashMap<string,Attribute*> attributeMap);
	void insertAllForeignKeyAttributes(HashMap<string,Attribute*> attributeMap);

	string getEntityID();
	string getEntityName();
	
	set<string> getAllPrimaryKeyAttributesNameSet();
	set<string> getAllDefaultKeyAttributesNameSet();
	set<string> getAllForeignKeyAttributesNameSet();
private:
	Entity* entity;
	HashMap<string,Attribute*> attributeMap;
	HashMap<string,Attribute*> foreignKeyAttributeMap;
};