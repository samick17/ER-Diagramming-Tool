#pragma once

#include "HashMap.h"
#include "TableManager.h"
#include "Entity.h"
#include "RelationShip.h"

class TableUtil{
    friend class TableUtil;
    FRIEND_TEST(TableUtilTest,testInsertAllEntitiesToTable);
    FRIEND_TEST(TableUtilTest,testGetOneToOneRelationShips);
    FRIEND_TEST(TableUtilTest,testInsertAllForeignKeyToTable);
    FRIEND_TEST(TableUtilTest,testConvertEmptyMap);
public:
    static HashMap<string,Table*> convertToTableMap(TableManager& tableManager,HashMap<string,Entity*> entityMap,HashMap<string,RelationShip*> relationShipMap);
private:
    static void insertAllEntitiesToTable(TableManager& tableManager,HashMap<string,Entity*> entityMap);
    static HashMap<string,RelationShip*> getOneToOneRelationShips(HashMap<string,RelationShip*> relationShipMap);    
    static void insertAllForeignKeyToTable(TableManager& tableManager,RelationShip* ontToOneRelationShip);
};