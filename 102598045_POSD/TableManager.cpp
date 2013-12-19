#include "TableManager.h"
#include "HashMapUtil.h"

TableManager::TableManager(){
}

TableManager::~TableManager(){
    this->clearAll();
}

void TableManager::insertTable(Table* table){
    //avoid duplicate table key, use try catch to put table
    try{
        this->tableMap.put(table->getEntityID(),table);
    }
    catch(Exception&){
    }
}

Table* TableManager::getTableByID(string id){
    return this->tableMap.get(id);
}

void TableManager::clearAll(){
    HashMapUtil::deleteAll(this->tableMap);
}

HashMap<string,Table*> TableManager::getAllTables(){
    return this->tableMap;
}