#pragma once

#include <unordered_map>
#include "Table.h"

typedef pair<string,Table*> TablePair;

class TableManager{
public:
	TableManager();
	~TableManager();

	void insertTable(Table* table);
	Table* getTableByID(string id);
	void clearAll();

	unordered_map<string,Table*> getAllTables();
private:
	unordered_map<string,Table*> tableMap;
};