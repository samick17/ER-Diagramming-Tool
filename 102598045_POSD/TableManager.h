#pragma once

#include <hash_map>
#include "Table.h"

typedef pair<string,Table*> TablePair;

class TableManager{
public:
	TableManager();
	~TableManager();

	void insertTable(Table* table);
	Table* getTableByID(string id);
	void clearAll();

	set<Table*> getAllTables();
private:
	hash_map<string,Table*> tableMap;
};