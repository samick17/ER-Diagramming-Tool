#include "AttributeTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

void AttributeTest::SetUp(){
	this->attribute = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
	this->relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	this->entity = this->erModel.addNode(ComponentType::TypeEntity);
}

void AttributeTest::TearDown(){
}

TEST_F(AttributeTest,testGetType){
	ASSERT_EQ(ComponentType::TypeAttribute,this->attribute->getType());
}

TEST_F(AttributeTest,testCanConnectTo){
	ASSERT_THROW(this->attribute->canConnectTo(this->relationShip),InvalidConnectException);
	ASSERT_THROW(this->relationShip->canConnectTo(this->attribute),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->attribute->canConnectTo(this->entity));
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(this->attribute));	
	ASSERT_THROW(this->attribute->canConnectTo(this->attribute),ConnectedSelfException);	

	this->erModel.addConnection(this->entity,this->attribute);
	ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
	ASSERT_THROW(this->attribute->canConnectTo(this->erModel.addNode(ComponentType::TypeAttribute)),InvalidConnectException);
	ASSERT_THROW(this->attribute->canConnectTo(this->erModel.addNode(ComponentType::TypeEntity)),InvalidConnectException);
}
TEST_F(AttributeTest,testHasSizeToConnect){
	ASSERT_EQ(true,this->attribute->hasSizeToConnect());
	ASSERT_EQ(true,this->relationShip->hasSizeToConnect());
	ASSERT_EQ(true,this->entity->hasSizeToConnect());

	this->erModel.addConnection(this->attribute,this->entity);
	ASSERT_EQ(false,this->attribute->hasSizeToConnect());
	this->erModel.addConnection(this->relationShip,this->entity);
	ASSERT_EQ(true,this->relationShip->hasSizeToConnect());

	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	this->erModel.addConnection(this->relationShip,entity2);
	ASSERT_EQ(false,this->relationShip->hasSizeToConnect());
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
	//assert map
	ASSERT_EQ(this->attribute->componentData,attributeCloned->componentData);

	delete attributeCloned;
}