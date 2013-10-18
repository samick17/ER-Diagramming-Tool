#include "ERModelUtil.h"

HashMap<string,Table*> ERModelUtil::convertToTableMap(TableManager& tableManager,HashMap<string,RelationShip*> relationShipSet){
	tableManager.clearAll();

	//get RelationShips & append Table of this relation type
	HashMap<string,RelationShip*> oneToOneRelationSet = getOneToOneRelationShips(relationShipSet);	
	appendOneToOneTable(tableManager,oneToOneRelationSet);

	return tableManager.getAllTables();
}

HashMap<string,RelationShip*> ERModelUtil::getOneToOneRelationShips(HashMap<string,RelationShip*> relationShipSet){
	HashMap<string,RelationShip*> oneToOneRelationShipsSet;
	for each(RelationShip* relationShip in relationShipSet){
		if(relationShip->isRelationType(RelationType::OneToOne))		
			oneToOneRelationShipsSet.put(relationShip->getID(),relationShip);
	}
	return oneToOneRelationShipsSet;
}
//append all table to tableManager
void ERModelUtil::appendOneToOneTable(TableManager& tableManager,HashMap<string,RelationShip*> oneToOneRelationSet){	
	for each(RelationShip* relationShip in oneToOneRelationSet){
		//convert entity to table
		for each(Entity* entity in relationShip->getConnectedEntities()){
			Table* table = new Table(entity);
			table->insertAllAttributes(entity->getConnectedAttributes());
			tableManager.insertTable(table);
		}
		//convert relationship data & insert data to table
		Entity* firstEntity = *relationShip->getConnectedEntities().begin();
		Entity* secondEntity = *(--relationShip->getConnectedEntities().end());
		HashMap<string,Attribute*> primaryKeyAttributeSet;
		Table* table = NULL;
		//find pk set & find table to insert pk
		if(!((primaryKeyAttributeSet = firstEntity->getPrimaryKeyAttributes()).empty()))
			table = tableManager.getTableByID(secondEntity->getID());
		else if(!((primaryKeyAttributeSet = secondEntity->getPrimaryKeyAttributes()).empty()))
			table = tableManager.getTableByID(firstEntity->getID());
		//insert all foreign key
		if(table != NULL)	
			table->insertAllForeignKeyAttributes(primaryKeyAttributeSet);		
	}
}