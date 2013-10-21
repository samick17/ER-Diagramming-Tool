#include "EntityTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "EmptyCollectionException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"
#include "NoConnectionException.h"

void EntityTest::SetUp(){
	this->attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	this->relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	this->entity = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
}

void EntityTest::TearDown(){
}

TEST_F(EntityTest,testToString){
	ASSERT_THROW(this->entity->toString(),EmptyCollectionException);

	this->erModel.addConnection(this->entity,this->attribute);
	(static_cast<Attribute*>(this->attribute))->setAsPrimaryKey();

	ASSERT_EQ("2 0",this->entity->toString());

	Attribute* attribute2 = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
	this->erModel.addConnection(this->entity,attribute2);
	attribute2->setAsPrimaryKey();

	ASSERT_EQ("2 0,4",this->entity->toString());
}

TEST_F(EntityTest,testGetType){
	ASSERT_EQ(ComponentType::TypeEntity,this->entity->getType());
}

TEST_F(EntityTest,testCanConnectTo){
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(this->attribute));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(this->relationShip));
	
	this->erModel.addConnection(this->entity,this->attribute);
	this->erModel.addConnection(this->entity,this->relationShip);

	ASSERT_THROW(this->entity->canConnectTo(this->entity),ConnectedSelfException);
	ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->relationShip),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->erModel.addNode(ComponentType::TypeEntity)),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(this->erModel.addNode(ComponentType::TypeAttribute)));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(this->erModel.addNode(ComponentType::TypeRelationShip)));
}

TEST_F(EntityTest,testGetConnectedAttributes){
	ASSERT_THROW(this->entity->getConnectedAttributes(),EmptyCollectionException);

	this->erModel.addConnection(this->entity,this->attribute);

	ASSERT_EQ(1,this->entity->getConnectedAttributes().size());

	ASSERT_EQ(this->attribute,this->entity->getConnectedAttributes().get(this->attribute->getID()));
}

TEST_F(EntityTest,testGetAttributeByID){
	this->erModel.addConnection(this->entity,this->attribute);
	ASSERT_THROW(this->entity->getAttributeByID("100"),NoConnectionException);
	ASSERT_EQ(this->attribute,this->entity->getAttributeByID(this->attribute->getID()));
}

TEST_F(EntityTest,testGetPrimaryKeyAttributes){
	this->erModel.addConnection(this->entity,this->attribute);

	ASSERT_EQ(0,this->entity->getPrimaryKeyAttributes().size());

	set<string> primaryKeyID;
	primaryKeyID.insert("0");
	this->entity->setPrimaryKey(primaryKeyID);

	ASSERT_EQ(1,this->entity->getPrimaryKeyAttributes().size());
	ASSERT_EQ(this->attribute,this->entity->getPrimaryKeyAttributes().get(this->attribute->getID()));
}

TEST_F(EntityTest,testSetPrimaryKey){
	set<string> primaryKeyID;
	primaryKeyID.insert("1");
	ASSERT_THROW(this->entity->setPrimaryKey(primaryKeyID),EmptyCollectionException);
	this->erModel.addConnection(this->entity,this->attribute);

	ASSERT_EQ(false,(static_cast<Attribute*>(this->attribute)->isPrimaryKey()));

	ASSERT_THROW(this->entity->setPrimaryKey(primaryKeyID),NoConnectionException);
	primaryKeyID.clear();
	primaryKeyID.insert("0");
	this->entity->setPrimaryKey(primaryKeyID);
	ASSERT_EQ(true,(static_cast<Attribute*>(this->attribute)->isPrimaryKey()));	
}

TEST_F(EntityTest,testClone){
	Entity* entityCloned = static_cast<Entity*>(this->entity->clone());

	ASSERT_EQ(this->entity->getID(),entityCloned->getID());
	ASSERT_EQ(this->entity->getName(),entityCloned->getName());
	ASSERT_EQ(this->entity->getType(),entityCloned->getType());
	//assert componentData
	ASSERT_EQ(this->entity->componentData,entityCloned->componentData);

	delete entityCloned;
}