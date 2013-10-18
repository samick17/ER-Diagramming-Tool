#pragma once
#include "Entity.h"
#include "Attribute.h"
#include <set>
#include <string>
#include "HashMap.h"

class Table{
	friend class ERModelTest;
	FRIEND_TEST(ERModelTest,testGetAllTables);
public:	
	Table(Entity* entity);
	~Table();
	
	void insertAllAttributes(HashMap<string,Attribute*> attributeSet);
	void insertAllForeignKeyAttributes(HashMap<string,Attribute*> attributeSet);

	string getEntityID();
	string getEntityName();
	
	set<string> getAllPrimaryKeyAttributesNameSet();
	set<string> getAllDefaultKeyAttributesNameSet();
	set<string> getAllForeignKeyAttributesNameSet();
private:
	Entity* entity;
	HashMap<string,Attribute*> attributeSet;
	HashMap<string,Attribute*> foreignKeyAttributeSet;
};