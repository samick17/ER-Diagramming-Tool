#include "TableUtil.h"

HashMap<string,Table*> TableUtil::convertToTableMap(TableManager& tableManager,HashMap<string,Entity*> entityMap,HashMap<string,RelationShip*> relationShipMap){
	tableManager.clearAll();

	insertAllEntitiesToTable(tableManager,entityMap);

	HashMap<string,RelationShip*> oneToOneRelationSet = getOneToOneRelationShips(relationShipMap);
	appendOneToOneTable(tableManager,oneToOneRelationSet);

	return tableManager.getAllTables();
}

void TableUtil::insertAllEntitiesToTable(TableManager& tableManager,HashMap<string,Entity*> entityMap){
	//get RelationShips & append Table of this relation type
	for each(Entity* entity in entityMap){
		Table* table = new Table(entity);
		try{
			table->insertAllAttributes(entity->getConnectedAttributes());
		}
		catch(Exception&){
		}
		tableManager.insertTable(table);			
	}
}

HashMap<string,RelationShip*> TableUtil::getOneToOneRelationShips(HashMap<string,RelationShip*> relationShipMap){
	HashMap<string,RelationShip*> oneToOneRelationShipsSet;
	for each(RelationShip* relationShip in relationShipMap){
		if(relationShip->isRelationType(RelationType::OneToOne))		
			oneToOneRelationShipsSet.put(relationShip->getID(),relationShip);
	}
	return oneToOneRelationShipsSet;
}
//append all table to tableManager
void TableUtil::appendOneToOneTable(TableManager& tableManager,HashMap<string,RelationShip*> oneToOneRelationMap){		
	for each(RelationShip* relationShip in oneToOneRelationMap){
		insertAllForeignKeyToTable(tableManager,relationShip);
	}
}
//insert All Foreign Key To Table
void TableUtil::insertAllForeignKeyToTable(TableManager& tableManager,RelationShip* relationShip){
	//convert relationship data & insert data to table
	Entity* firstEntity = *relationShip->getConnectedEntities().begin();
	Entity* secondEntity = *(--relationShip->getConnectedEntities().end());		
	HashMap<string,Attribute*> primaryKeyAttributeMap;
	//find pk set & find table to insert pk
	try{
		Table* table = NULL;
		if(!((primaryKeyAttributeMap = firstEntity->getPrimaryKeyAttributes()).empty()))
			table = tableManager.getTableByID(secondEntity->getID());
		else if(!((primaryKeyAttributeMap = secondEntity->getPrimaryKeyAttributes()).empty()))
			table = tableManager.getTableByID(firstEntity->getID());
		//insert all foreign key
		table->insertAllForeignKeyAttributes(primaryKeyAttributeMap);
	}catch(Exception&){
	}
}