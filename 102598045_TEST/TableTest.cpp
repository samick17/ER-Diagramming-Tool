#include "TableTest.h"
#include "HashMapUtil.h"

void TableTest::SetUp(){
    this->entity = new Entity("0","PC");
    table = new Table(this->entity);
    Attribute* name = new Attribute("1","Name");
    Attribute* age = new Attribute("2","Age");
    Attribute* id = new Attribute("3","ID");
    Attribute* empID = new Attribute("4","Emp_ID");
    id->setAsPrimaryKey();
    empID->setAsPrimaryKey();
    this->defaultAttributeMap.put(name->getID(),name);
    this->defaultAttributeMap.put(age->getID(),age);
    this->primaryKeyAttributeMap.put(id->getID(),id);
    this->foreignKeyAttributeMap.put(empID->getID(),empID);
}

void TableTest::TearDown(){
    delete this->entity;
    delete this->table;
    HashMapUtil::deleteAll(this->defaultAttributeMap);
    HashMapUtil::deleteAll(this->primaryKeyAttributeMap);
    HashMapUtil::deleteAll(this->foreignKeyAttributeMap);
}

TEST_F(TableTest,testInsertAllAttributes){
    ASSERT_EQ(0,this->table->allAttributeMap.size());
    ASSERT_EQ(0,this->table->primaryKeyAttributeMap.size());
    ASSERT_EQ(0,this->table->defaultAttributeMap.size());
    ASSERT_EQ(0,this->table->foreignKeyAttributeMap.size());
    this->table->insertAllAttributes(this->defaultAttributeMap);
    ASSERT_EQ(this->defaultAttributeMap.size(),this->table->allAttributeMap.size());
    ASSERT_EQ(0,this->table->primaryKeyAttributeMap.size());
    ASSERT_EQ(this->defaultAttributeMap.size(),this->table->defaultAttributeMap.size());
    ASSERT_EQ(0,this->table->foreignKeyAttributeMap.size());
    this->table->insertAllAttributes(this->primaryKeyAttributeMap);
    ASSERT_EQ(this->defaultAttributeMap.size()+this->primaryKeyAttributeMap.size(),this->table->allAttributeMap.size());
    ASSERT_EQ(this->primaryKeyAttributeMap.size(),this->table->primaryKeyAttributeMap.size());
    ASSERT_EQ(this->defaultAttributeMap.size(),this->table->defaultAttributeMap.size());
    ASSERT_EQ(0,this->table->foreignKeyAttributeMap.size());
}

TEST_F(TableTest,testInsertAllForeignKeyAttributes){
    ASSERT_EQ(0,this->table->allAttributeMap.size());
    ASSERT_EQ(0,this->table->primaryKeyAttributeMap.size());
    ASSERT_EQ(0,this->table->defaultAttributeMap.size());
    ASSERT_EQ(0,this->table->foreignKeyAttributeMap.size());
    this->table->insertAllForeignKeyAttributes(this->foreignKeyAttributeMap);
    ASSERT_EQ(this->foreignKeyAttributeMap.size(),this->table->allAttributeMap.size());
    ASSERT_EQ(0,this->table->primaryKeyAttributeMap.size());
    ASSERT_EQ(0,this->table->defaultAttributeMap.size());
    ASSERT_EQ(this->foreignKeyAttributeMap.size(),this->table->foreignKeyAttributeMap.size());
}

TEST_F(TableTest,testGetTableID){
    ASSERT_EQ(this->entity->getID(),this->table->getTableID());
}

TEST_F(TableTest,testGetTableName){
    ASSERT_EQ(this->entity->getName(),this->table->getTableName());
}

TEST_F(TableTest,testToString){
    this->table->primaryKeyAttributeMap = this->primaryKeyAttributeMap;
    this->table->defaultAttributeMap = this->defaultAttributeMap;
    this->table->foreignKeyAttributeMap = this->foreignKeyAttributeMap;
    for each(Attribute* attribute in this->primaryKeyAttributeMap)
        this->table->allAttributeMap.put(attribute->getID(),attribute);
    for each(Attribute* attribute in this->defaultAttributeMap)
        this->table->allAttributeMap.put(attribute->getID(),attribute);
    for each(Attribute* attribute in this->foreignKeyAttributeMap)
        this->table->allAttributeMap.put(attribute->getID(),attribute);
    ASSERT_EQ(" PK(ID),Name,Age, FK(Emp_ID)",this->table->toString());
}

TEST_F(TableTest,testAppendAttributeToString){
    ASSERT_EQ("ID",this->table->appendAttributeToString(this->primaryKeyAttributeMap));
    ASSERT_EQ("Name,Age",this->table->appendAttributeToString(this->defaultAttributeMap));
    ASSERT_EQ("Emp_ID",this->table->appendAttributeToString(this->foreignKeyAttributeMap));

    ASSERT_EQ(" PK(ID)",this->table->appendAttributeToString(this->primaryKeyAttributeMap," PK(",")"));
    ASSERT_EQ(" FK(Emp_ID)",this->table->appendAttributeToString(this->foreignKeyAttributeMap," FK(",")"));
}