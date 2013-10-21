#include "RelationShipTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

void RelationShipTest::SetUp(){
	this->attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	this->relationShip = static_cast<RelationShip*>(this->erModel.addNode(ComponentType::TypeRelationShip));
	this->entity = this->erModel.addNode(ComponentType::TypeEntity);
}

void RelationShipTest::TearDown(){
}

TEST_F(RelationShipTest,testGetType){
	ASSERT_EQ(ComponentType::TypeRelationShip,this->relationShip->getType());
}
		
TEST_F(RelationShipTest,CanConnectTo){
	ASSERT_THROW(this->relationShip->canConnectTo(this->attribute),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->relationShip->canConnectTo(this->entity));	
	ASSERT_THROW(this->relationShip->canConnectTo(this->relationShip),ConnectedSelfException);

	this->erModel.addConnection(this->entity,this->relationShip);
	ASSERT_THROW(this->relationShip->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->relationShip->canConnectTo(this->erModel.addNode(ComponentType::TypeRelationShip)),InvalidConnectException);
	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	this->erModel.addConnection(entity2,this->relationShip);
	ASSERT_THROW(this->relationShip->canConnectTo(this->erModel.addNode(ComponentType::TypeEntity)),InvalidConnectException);
}

TEST_F(RelationShipTest,testHasSizeToConnect){
	ASSERT_EQ(true,this->attribute->hasSizeToConnect());
	ASSERT_EQ(true,this->relationShip->hasSizeToConnect());
	ASSERT_EQ(true,this->entity->hasSizeToConnect());

	this->erModel.addConnection(this->relationShip,this->entity);
	ASSERT_EQ(true,this->relationShip->hasSizeToConnect());

	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	this->erModel.addConnection(this->relationShip,entity2);
	ASSERT_EQ(false,this->relationShip->hasSizeToConnect());
}

TEST_F(RelationShipTest,testIsRelationType){	
	ASSERT_EQ(false,this->relationShip->isRelationType("X"));
	
	ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::OneToOne));

	this->erModel.addConnection(this->relationShip,this->entity);
	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	this->erModel.addConnection(this->relationShip,entity2);
	ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::OneToOne));
	Component* connector1 = this->erModel.getComponentByID("3");
	Component* connector2 = this->erModel.getComponentByID("5");
	connector1->setName(RelationType::OneToOne);
	ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::OneToOne));
	connector2->setName(RelationType::OneToOne);
	ASSERT_EQ(true,this->relationShip->isRelationType(RelationType::OneToOne));
}

TEST_F(RelationShipTest,testGetConnectedEntities){
	ASSERT_EQ(0,this->relationShip->getConnectedEntities().size());
	this->erModel.addConnection(this->relationShip,this->entity);
	ASSERT_EQ(1,this->relationShip->getConnectedEntities().size());
	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	this->erModel.addConnection(this->relationShip,entity2);
	ASSERT_EQ(2,this->relationShip->getConnectedEntities().size());

	Component* entity3 = this->erModel.addNode(ComponentType::TypeEntity);
	ASSERT_THROW(this->erModel.addConnection(this->relationShip,entity3),InvalidConnectException);
}

TEST_F(RelationShipTest,testClone){
	RelationShip* relationShipCloned = static_cast<RelationShip*>(this->relationShip->clone());

	ASSERT_EQ(this->relationShip->getID(),relationShipCloned->getID());
	ASSERT_EQ(this->relationShip->getName(),relationShipCloned->getName());
	ASSERT_EQ(this->relationShip->getType(),relationShipCloned->getType());
	//assert componentData
	ASSERT_EQ(this->relationShip->componentData,relationShipCloned->componentData);

	delete relationShipCloned;
}