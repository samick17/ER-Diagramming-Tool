#include "ERModelUtil.h"

unordered_map<string,Table*> ERModelUtil::convertToTableMap(TableManager& tableManager,set<RelationShip*> relationShipSet){
	tableManager.clearAll();

	//get RelationShips & append Table of this relation type
	set<RelationShip*> oneToOneRelationSet = getOneToOneRelationShips(relationShipSet);	
	appendOneToOneTable(tableManager,oneToOneRelationSet);

	return tableManager.getAllTables();
}

set<RelationShip*> ERModelUtil::getOneToOneRelationShips(set<RelationShip*> relationShipSet){
	set<RelationShip*> oneToOneRelationShipsSet;
	for each(RelationShip* relationShip in relationShipSet){
		if(relationShip->isRelationType(RelationType::OneToOne))		
			oneToOneRelationShipsSet.insert(relationShip);
	}
	return oneToOneRelationShipsSet;
}
//append all table to tableManager
void ERModelUtil::appendOneToOneTable(TableManager& tableManager,set<RelationShip*> oneToOneRelationSet){	
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
		set<Attribute*> primaryKeyAttributeSet;
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