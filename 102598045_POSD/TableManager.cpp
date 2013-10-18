#include "TableManager.h"

TableManager::TableManager(){
}

TableManager::~TableManager(){
	this->clearAll();
}

void TableManager::insertTable(Table* table){
	try{
		this->tableMap.put(table->getEntityID(),table);
	}catch(Exception&){
	}
}

Table* TableManager::getTableByID(string id){	
	return this->tableMap.get(id);
}

void TableManager::clearAll(){
	for each(Table* table in this->tableMap)
		delete table;
	this->tableMap.clear();
}

HashMap<string,Table*> TableManager::getAllTables(){
	return this->tableMap;
}