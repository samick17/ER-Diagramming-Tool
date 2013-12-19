#include "TableTest.h"

void TableTest::SetUp(){
    entity = new Entity("0","Engineer");
    table = new Table(entity);

	ASSERT_EQ(0,table->allAttributeMap.size());
    ASSERT_EQ(0,table->foreignKeyAttributeMap.size());

    Attribute* attributeName = new Attribute("1","Name");
    attributeName->setAsPrimaryKey();
    Attribute* attributeID = new Attribute("2","Emp_ID");
    attributeID->setAsPrimaryKey();
    Attribute* attributeAge = new Attribute("3","Age");
    this->attributeMap.put(attributeName->getID(),attributeName);
    this->attributeMap.put(attributeID->getID(),attributeID);
    this->attributeMap.put(attributeAge->getID(),attributeAge);

    Attribute* attributePC_ID = new Attribute("4","PC_ID");
    attributePC_ID->setAsPrimaryKey();
    Attribute* attributeValue = new Attribute("5","Purchase_Date");
    this->foreignKeyAttributeMap.put(attributePC_ID->getID(),attributePC_ID);
    this->foreignKeyAttributeMap.put(attributeValue->getID(),attributeValue);

    this->table->allAttributeMap = this->attributeMap;
    this->table->foreignKeyAttributeMap = this->foreignKeyAttributeMap;

    ASSERT_EQ(3,table->allAttributeMap.size());
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
    Attribute* attributeSex = new Attribute("6","Sex");
    Attribute* attributeDepartment = new Attribute("8","Department");
    Attribute* attributeWeight = new Attribute("13","Weight");
    attributeMapInsert.put(attributeSex->getID(),attributeSex);
    attributeMapInsert.put(attributeDepartment->getID(),attributeDepartment);
    attributeMapInsert.put(attributeWeight->getID(),attributeWeight);
    this->table->insertAllAttributes(attributeMapInsert);

    ASSERT_EQ(6,this->table->allAttributeMap.size());

    ASSERT_EQ(attributeSex,this->table->allAttributeMap.get("6"));
    ASSERT_EQ(attributeDepartment,this->table->allAttributeMap.get("8"));
    ASSERT_EQ(attributeWeight,this->table->allAttributeMap.get("13"));
}

TEST_F(TableTest,testInsertAllForeignKeyAttributes){
    HashMap<string,Attribute*> foreignKeyAttributeMapInsert;
    ASSERT_EQ(2,this->table->foreignKeyAttributeMap.size());
    Attribute* attributeSex = new Attribute("10","Sex");
    Attribute* attributeDepartment = new Attribute("20","Department");
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
    vector<string> primaryKeySet = this->table->getAllPrimaryKeyAttributesNameVector();
    ASSERT_EQ(2,primaryKeySet.size());
    ASSERT_EQ(attributeMap.get("1")->getName(),primaryKeySet[0]);
    ASSERT_EQ(attributeMap.get("2")->getName(),primaryKeySet[1]);

    ASSERT_EQ("Name",primaryKeySet[0]);
    ASSERT_EQ("Emp_ID",primaryKeySet[1]);
}

TEST_F(TableTest,testGetAllDefaultKeyAttributesNameSet){
    vector<string> defaultKeySet = this->table->getAllDefaultKeyAttributesNameVector();
    ASSERT_EQ(1,defaultKeySet.size());
    ASSERT_EQ(attributeMap.get("3")->getName(),defaultKeySet[0]);

    ASSERT_EQ("Age",defaultKeySet[0]);
}

TEST_F(TableTest,testGetAllForeignKeyAttributesNameSet){
    vector<string> foreignKeySet = this->table->getAllForeignKeyAttributesNameVector();
    ASSERT_EQ(2,foreignKeySet.size());
    ASSERT_EQ(foreignKeyAttributeMap.get("4")->getName(),foreignKeySet[0]);
    ASSERT_EQ(foreignKeyAttributeMap.get("5")->getName(),foreignKeySet[1]);

    ASSERT_EQ("PC_ID",foreignKeySet[0]);
    ASSERT_EQ("Purchase_Date",foreignKeySet[1]);
}