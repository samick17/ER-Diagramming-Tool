#pragma once

#include "HashMap.h"
#include "TableManager.h"
#include "Entity.h"
#include "RelationShip.h"

class TableUtil{
public:
	static HashMap<string,Table*> convertToTableMap(TableManager& tableManager,HashMap<string,Entity*> entityMap,HashMap<string,RelationShip*> relationShipMap);
private:
	static void insertAllEntitiesToTable(TableManager& tableManager,HashMap<string,Entity*> entityMap);
	static HashMap<string,RelationShip*> getOneToOneRelationShips(HashMap<string,RelationShip*> relationShipMap);
	static void appendOneToOneTable(TableManager& tableManager,HashMap<string,RelationShip*> relationShipMap);	
	static void insertAllForeignKeyToTable(TableManager& tableManager,RelationShip* relationShip);
};