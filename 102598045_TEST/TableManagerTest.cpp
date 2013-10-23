#include "TableManagerTest.h"
#include "NoSuchKeyException.h"

void TableManagerTest::SetUp(){		
}

void TableManagerTest::TearDown(){	
}

TEST_F(TableManagerTest,testInsertTable){	
	//insert & assert size
	ASSERT_EQ(0,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(new Table(&Entity(ComponentData("0","Character"))));
	ASSERT_EQ(1,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(new Table(&Entity(ComponentData("1","Account"))));
	ASSERT_EQ(2,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(new Table(&Entity(ComponentData("2","Guide"))));
	ASSERT_EQ(3,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(new Table(&Entity(ComponentData("3","Friend"))));
	ASSERT_EQ(4,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(new Table(&Entity(ComponentData("4","Scene"))));
	ASSERT_EQ(5,this->tableManager.getAllTables().size());
}

TEST_F(TableManagerTest,testGetTableByID){
	Entity* entityCharacter = new Entity(ComponentData("0","Character"));
	Entity* entityAccount = new Entity(ComponentData("1","Account"));
	Entity* entityGuide = new Entity(ComponentData("2","Guide"));

	Table* tableCharacter = new Table(entityCharacter);
	Table* tableAccount = new Table(entityAccount);
	Table* tableGuide = new Table(entityGuide);
	
	ASSERT_EQ(0,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(tableCharacter);
	ASSERT_EQ(1,this->tableManager.getAllTables().size());
	
	this->tableManager.insertTable(tableAccount);
	ASSERT_EQ(2,this->tableManager.getAllTables().size());
	
	this->tableManager.insertTable(tableGuide);
	ASSERT_EQ(3,this->tableManager.getAllTables().size());
	
	ASSERT_EQ(tableCharacter,this->tableManager.getTableByID(tableCharacter->getEntityID()));
	ASSERT_EQ(tableAccount,this->tableManager.getTableByID(tableAccount->getEntityID()));
	ASSERT_EQ(tableGuide,this->tableManager.getTableByID(tableGuide->getEntityID()));
	ASSERT_THROW(this->tableManager.getTableByID("NoSuchKeyTableID"),NoSuchKeyException);

	delete entityCharacter;
	delete entityAccount;
	delete entityGuide;
}

TEST_F(TableManagerTest,testClearAll){
	ASSERT_EQ(0,this->tableManager.getAllTables().size());
	this->tableManager.insertTable(new Table(&Entity(ComponentData("0","Character"))));
	this->tableManager.insertTable(new Table(&Entity(ComponentData("1","Account"))));
	this->tableManager.insertTable(new Table(&Entity(ComponentData("3","Friend"))));
	ASSERT_EQ(3,this->tableManager.getAllTables().size());
	this->tableManager.clearAll();
	ASSERT_EQ(0,this->tableManager.getAllTables().size());
}