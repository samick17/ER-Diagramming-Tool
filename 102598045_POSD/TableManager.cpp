#include "TableManager.h"

TableManager::TableManager(){
}

TableManager::~TableManager(){
	this->clearAll();
}

void TableManager::insertTable(Table* table){
	this->tableMap.insert(TablePair(table->getEntityID(),table));
}

Table* TableManager::getTableByID(string id){
	hash_map<string,Table*>::iterator tableIterator;
	if((tableIterator = this->tableMap.find(id)) != this->tableMap.end())	
		return tableIterator->second;
	
	return NULL;
}

void TableManager::clearAll(){
	for each(TablePair tablePair in this->tableMap){
		delete tablePair.second;
		tablePair.second = NULL;
	}
	
	this->tableMap.clear();
}

unordered_map<string,Table*> TableManager::getAllTables(){
	return this->tableMap;
}