#pragma once
#include "Entity.h"
#include "Attribute.h"
#include <hash_map>
#include <set>
#include <string>

class Table{
public:	
	Table(Entity* entity);
	~Table();
	
	void insertAllAttributes(set<Attribute*> attributeSet);
	void insertAllForeignKeyAttributes(set<Attribute*> attributeSet);

	string getEntityID();
	string getEntityName();
	
	set<string> getAllPrimaryKeyAttributesNameSet();
	set<string> getAllDefaultKeyAttributesNameSet();
	set<string> getAllForeignKeyAttributesNameSet();
private:
	Entity* entity;
	set<Attribute*> attributeSet;
	set<Attribute*> foreignKeyAttributeSet;
};