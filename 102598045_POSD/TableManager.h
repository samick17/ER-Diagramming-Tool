#pragma once

#include "HashMap.h"
#include "Table.h"

class TableManager{
public:
    TableManager();
    ~TableManager();

    void insertTable(Table* table);
    Table* getTableByID(string id);
    void clearAll();

    HashMap<string,Table*> getAllTables();
private:
    HashMap<string,Table*> tableMap;
};