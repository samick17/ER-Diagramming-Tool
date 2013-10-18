#include "TableManager.h"

TableManager::TableManager(){
}

TableManager::~TableManager(){
	this->clearAll();
}

void TableManager::insertTable(Table* table){
	this->tableMap.put(table->getEntityID(),table);
}

Table* TableManager::getTableByID(string id){	
	if(this->tableMap.containsKey(id))
		return this->tableMap.get(id);
	
	return NULL;
}

void TableManager::clearAll(){
	for each(Table* table in this->tableMap)
		delete table;
	this->tableMap.clear();
}

HashMap<string,Table*> TableManager::getAllTables(){
	return this->tableMap;
}