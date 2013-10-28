#pragma once
#include "Entity.h"
#include "Attribute.h"
#include <string>
#include "HashMap.h"

class Table{
    friend class ERModelTest;
    FRIEND_TEST(ERModelTest,testGetAllTables);
    friend class TableTest;
    FRIEND_TEST(TableTest,testInsertAllAttributes);
    FRIEND_TEST(TableTest,testInsertAllForeignKeyAttributes);
    friend class TableUtilTest;
    FRIEND_TEST(TableUtilTest,testInsertAllEntitiesToTable);
public:    
    Table(Entity* entity);
    ~Table();
    
    void insertAllAttributes(HashMap<string,Attribute*> attributeMap);
    void insertAllForeignKeyAttributes(HashMap<string,Attribute*> attributeMap);

    string getEntityID();
    string getEntityName();
    
    vector<string> getAllPrimaryKeyAttributesNameVector();
    vector<string> getAllDefaultKeyAttributesNameVector();
    vector<string> getAllForeignKeyAttributesNameVector();
private:
    Entity* entity;
    HashMap<string,Attribute*> attributeMap;
    HashMap<string,Attribute*> foreignKeyAttributeMap;
};