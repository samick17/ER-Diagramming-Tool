#include "AttributeTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

void AttributeTest::SetUp(){
	this->attribute = new Attribute(ComponentData("0","Name"));
	this->relationShip = new RelationShip(ComponentData("1","Has"));
	this->entity = new Entity(ComponentData("2","Engineer"));
}

void AttributeTest::TearDown(){
	delete this->attribute;
	delete this->relationShip;
	delete this->entity;
}

void AttributeTest::connectWithEachOther(Node* firstNode,Node* secondNode,Connector* connector){
	firstNode->connectTo(connector);
	secondNode->connectTo(connector);
	connector->connectTo(firstNode);
	connector->connectTo(secondNode);
}

TEST_F(AttributeTest,testGetType){
	ASSERT_EQ(ComponentType::TypeAttribute,this->attribute->getType());
}

TEST_F(AttributeTest,testCanConnectTo){
	ASSERT_THROW(this->attribute->canConnectTo(this->relationShip),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->attribute->canConnectTo(this->entity));	
	ASSERT_THROW(this->attribute->canConnectTo(this->attribute),ConnectedSelfException);	

	Connector* connector = new Connector(ComponentData("3",""));	
	this->connectWithEachOther(this->attribute,this->entity,connector);

	ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);	
	ASSERT_THROW(this->attribute->canConnectTo(&Attribute(ComponentData("",""))),InvalidConnectException);
	ASSERT_THROW(this->attribute->canConnectTo(&Entity(ComponentData("",""))),InvalidConnectException);

	delete connector;
}
TEST_F(AttributeTest,testHasSizeToConnect){
	ASSERT_EQ(true,this->attribute->hasSizeToConnect());

	Connector* connector = new Connector(ComponentData("3",""));	
	this->connectWithEachOther(this->attribute,this->entity,connector);
	ASSERT_EQ(false,this->attribute->hasSizeToConnect());
}

TEST_F(AttributeTest,testIsPrimaryKey){
	ASSERT_EQ(false,this->attribute->isPrimaryKey());
	this->attribute->setAsPrimaryKey();
	ASSERT_EQ(true,this->attribute->isPrimaryKey());
}

TEST_F(AttributeTest,testSetAsPrimaryKey){
	ASSERT_EQ(false,this->attribute->isPrimaryKey());
	this->attribute->setAsPrimaryKey();
	ASSERT_EQ(true,this->attribute->isPrimaryKey());
}

TEST_F(AttributeTest,testClone){
	Attribute* attributeCloned = static_cast<Attribute*>(this->attribute->clone());

	ASSERT_EQ(this->attribute->getID(),attributeCloned->getID());
	ASSERT_EQ(this->attribute->getName(),attributeCloned->getName());
	ASSERT_EQ(this->attribute->getType(),attributeCloned->getType());
	//assert componentData
	ASSERT_EQ(this->attribute->componentData,attributeCloned->componentData);

	delete attributeCloned;
}