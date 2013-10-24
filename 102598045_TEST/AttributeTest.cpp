#include "AttributeTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"
#include "ComponentUtil.h"

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

TEST_F(AttributeTest,testGetType){
	ASSERT_EQ(ComponentType::TypeAttribute,this->attribute->getType());
}

TEST_F(AttributeTest,testCanConnectTo){
	ASSERT_THROW(this->attribute->canConnectTo(this->relationShip),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->attribute->canConnectTo(this->entity));	
	ASSERT_THROW(this->attribute->canConnectTo(this->attribute),ConnectedSelfException);	

	Connector connector = Connector(ComponentData("3",""));	
	ComponentUtil::connectWithEachOther(this->attribute,this->entity,&connector);

	ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);	
	ASSERT_THROW(this->attribute->canConnectTo(&Attribute(ComponentData("",""))),InvalidConnectException);
	ASSERT_THROW(this->attribute->canConnectTo(&Entity(ComponentData("",""))),InvalidConnectException);
}
TEST_F(AttributeTest,testHasSizeToConnect){
	ASSERT_EQ(true,this->attribute->hasSizeToConnect());

	Connector connector = Connector(ComponentData("3",""));	
	ComponentUtil::connectWithEachOther(this->attribute,this->entity,&connector);
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