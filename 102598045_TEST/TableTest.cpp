#include "TableTest.h"

void TableTest::SetUp(){
	entity = new Entity(ComponentData("0","Engineer"));
	table = new Table(entity);

	ASSERT_EQ(0,table->attributeMap.size());
	ASSERT_EQ(0,table->foreignKeyAttributeMap.size());

	Attribute* attributeName = new Attribute(ComponentData("1","Name"));
	attributeName->setAsPrimaryKey();
	Attribute* attributeID = new Attribute(ComponentData("2","Emp_ID"));
	attributeID->setAsPrimaryKey();	
	Attribute* attributeAge = new Attribute(ComponentData("3","Age"));
	this->attributeMap.put(attributeName->getID(),attributeName);
	this->attributeMap.put(attributeID->getID(),attributeID);
	this->attributeMap.put(attributeAge->getID(),attributeAge);

	Attribute* attributePC_ID = new Attribute(ComponentData("4","PC_ID"));
	attributePC_ID->setAsPrimaryKey();
	Attribute* attributeValue = new Attribute(ComponentData("5","Purchase_Date"));	
	this->foreignKeyAttributeMap.put(attributePC_ID->getID(),attributePC_ID);
	this->foreignKeyAttributeMap.put(attributeValue->getID(),attributeValue);

	this->table->attributeMap = this->attributeMap;
	this->table->foreignKeyAttributeMap = this->foreignKeyAttributeMap;

	ASSERT_EQ(3,table->attributeMap.size());
	ASSERT_EQ(2,table->foreignKeyAttributeMap.size());
}

void TableTest::TearDown(){	
	delete this->entity;
	delete this->table;
	this->deleteAndClearHashMap(this->attributeMap);
	this->deleteAndClearHashMap(this->foreignKeyAttributeMap);	
	ASSERT_EQ(0,this->attributeMap.size());
	ASSERT_EQ(0,this->foreignKeyAttributeMap.size());	
}

void TableTest::deleteAndClearHashMap(HashMap<string,Attribute*>& attributeMap){
	for each(Attribute* attribute in attributeMap){
		delete attribute;
	}
	attributeMap.clear();
}

TEST_F(TableTest,testInsertAllAttributes){
	HashMap<string,Attribute*> attributeMapInsert;
	Attribute* attributeSex = new Attribute(ComponentData("6","Sex"));
	Attribute* attributeDepartment = new Attribute(ComponentData("8","Department"));
	Attribute* attributeWeight = new Attribute(ComponentData("13","Weight"));
	attributeMapInsert.put(attributeSex->getID(),attributeSex);
	attributeMapInsert.put(attributeDepartment->getID(),attributeDepartment);
	attributeMapInsert.put(attributeWeight->getID(),attributeWeight);
	this->table->insertAllAttributes(attributeMapInsert);

	ASSERT_EQ(6,this->table->attributeMap.size());

	ASSERT_EQ(attributeSex,this->table->attributeMap.get("6"
		));
	ASSERT_EQ(attributeDepartment,this->table->attributeMap.get("8"));
	ASSERT_EQ(attributeWeight,this->table->attributeMap.get("13"));
}

TEST_F(TableTest,testInsertAllForeignKeyAttributes){
	HashMap<string,Attribute*> foreignKeyAttributeMapInsert;
	ASSERT_EQ(2,this->table->foreignKeyAttributeMap.size());
	Attribute* attributeSex = new Attribute(ComponentData("10","Sex"));
	Attribute* attributeDepartment = new Attribute(ComponentData("20","Department"));
	foreignKeyAttributeMapInsert.put(attributeSex->getID(),attributeSex);
	foreignKeyAttributeMapInsert.put(attributeDepartment->getID(),attributeDepartment);
	this->table->insertAllForeignKeyAttributes(foreignKeyAttributeMapInsert);

	ASSERT_EQ(4,this->table->foreignKeyAttributeMap.size());

	ASSERT_EQ(attributeSex,this->table->foreignKeyAttributeMap.get("10"));
	ASSERT_EQ(attributeDepartment,this->table->foreignKeyAttributeMap.get("20"));
}

TEST_F(TableTest,testGetEntityID){
	ASSERT_EQ(this->entity->getID(),this->table->getEntityID());
}

TEST_F(TableTest,testGetEntityName){
	ASSERT_EQ(this->entity->getName(),this->table->getEntityName());
}

TEST_F(TableTest,testGetAllPrimaryKeyAttributesNameSet){
	set<string> primaryKeySet = this->table->getAllPrimaryKeyAttributesNameSet();
	ASSERT_EQ(2,primaryKeySet.size());
	ASSERT_NE(primaryKeySet.end(),primaryKeySet.find(attributeMap.get("1")->getName()));
	ASSERT_NE(primaryKeySet.end(),primaryKeySet.find(attributeMap.get("2")->getName()));
	ASSERT_EQ(primaryKeySet.end(),primaryKeySet.find(attributeMap.get("3")->getName()));

	ASSERT_NE(primaryKeySet.end(),primaryKeySet.find("Name"));
	ASSERT_NE(primaryKeySet.end(),primaryKeySet.find("Emp_ID"));
	ASSERT_EQ(primaryKeySet.end(),primaryKeySet.find("Age"));
}

TEST_F(TableTest,testGetAllDefaultKeyAttributesNameSet){
	set<string> defaultKeySet = this->table->getAllDefaultKeyAttributesNameSet();
	ASSERT_EQ(1,defaultKeySet.size());
	ASSERT_EQ(defaultKeySet.end(),defaultKeySet.find(attributeMap.get("1")->getName()));
	ASSERT_EQ(defaultKeySet.end(),defaultKeySet.find(attributeMap.get("2")->getName()));
	ASSERT_NE(defaultKeySet.end(),defaultKeySet.find(attributeMap.get("3")->getName()));

	ASSERT_EQ(defaultKeySet.end(),defaultKeySet.find("Name"));
	ASSERT_EQ(defaultKeySet.end(),defaultKeySet.find("Emp_ID"));
	ASSERT_NE(defaultKeySet.end(),defaultKeySet.find("Age"));
}

TEST_F(TableTest,testGetAllForeignKeyAttributesNameSet){
	set<string> foreignKeySet = this->table->getAllForeignKeyAttributesNameSet();
	ASSERT_EQ(2,foreignKeySet.size());
	ASSERT_NE(foreignKeySet.end(),foreignKeySet.find(foreignKeyAttributeMap.get("4")->getName()));
	ASSERT_NE(foreignKeySet.end(),foreignKeySet.find(foreignKeyAttributeMap.get("5")->getName()));

	ASSERT_NE(foreignKeySet.end(),foreignKeySet.find("PC_ID"));
	ASSERT_NE(foreignKeySet.end(),foreignKeySet.find("Purchase_Date"));
}