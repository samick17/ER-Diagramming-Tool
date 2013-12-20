#pragma once

#include <string>
#include "HashMap.h"
#include "StringSymbol.h"
#include <gtest/gtest_prod.h>

class Attribute;
class Entity;
class RelationShip;
class Node;

class Table{
    friend class ERModelTest;
    FRIEND_TEST(ERModelTest,testGetAllTables);
    FRIEND_TEST(ERModelTest,testCommonUsage);
    FRIEND_TEST(ERModelTest,testIsPrimaryExist);
    friend class TableTest;
    FRIEND_TEST(TableTest,testInsertAllAttributes);
    FRIEND_TEST(TableTest,testInsertAllForeignKeyAttributes);
    FRIEND_TEST(TableTest,testToString);
    FRIEND_TEST(TableTest,testAppendAttributeToString);
    friend class TableUtilTest;
    FRIEND_TEST(TableUtilTest,testConvertToTableMap);
    FRIEND_TEST(TableUtilTest,testInsertAllEntitiesToTable);
    FRIEND_TEST(TableUtilTest,testInsertAllForeignKeyToTable);
public:
    Table(Entity* entity);
    Table(RelationShip* relationShip);
    ~Table();
    
    void insertAllAttributes(HashMap<string,Attribute*> attributeMap);
    void insertAllForeignKeyAttributes(HashMap<string,Attribute*> attributeMap);

    string getTableID();
    string getTableName();

    HashMap<string,Attribute*> getAllAttributeMap();
    int getAttributeType(Attribute* attribute);

    string toString();
private:
    string appendAttributeToString(HashMap<string,Attribute*> attributeMap,string startString = StringSymbol::Empty,string endString = StringSymbol::Empty);
    Node* node;
    HashMap<string,Attribute*> allAttributeMap;
    HashMap<string,Attribute*> primaryKeyAttributeMap;
    HashMap<string,Attribute*> defaultAttributeMap;
    HashMap<string,Attribute*> foreignKeyAttributeMap;
};