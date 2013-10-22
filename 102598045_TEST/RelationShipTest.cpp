#include "RelationShipTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

void RelationShipTest::SetUp(){
	this->attribute = new Attribute(ComponentData("0","Name"));
	this->relationShip = new RelationShip(ComponentData("1","Has"));
	this->entity = new Entity(ComponentData("2","Engineer"));
}

void RelationShipTest::TearDown(){
	delete this->attribute;
	delete this->relationShip;
	delete this->entity;
}

TEST_F(RelationShipTest,testGetType){
	ASSERT_EQ(ComponentType::TypeRelationShip,this->relationShip->getType());
}
		
TEST_F(RelationShipTest,CanConnectTo){
	ASSERT_THROW(this->relationShip->canConnectTo(this->attribute),InvalidConnectException);
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->relationShip->canConnectTo(this->entity));	
	ASSERT_THROW(this->relationShip->canConnectTo(this->relationShip),ConnectedSelfException);

	Connector connector1 = Connector(ComponentData("3",""));
	connectWithEachOther(this->entity,this->relationShip,&connector1);
	ASSERT_THROW(this->relationShip->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->relationShip->canConnectTo(&RelationShip(ComponentData("4","WorkOn"))),InvalidConnectException);
	Entity entity2 = Entity(ComponentData("5","PC"));
	Connector connector2 = Connector(ComponentData("6",""));
	connectWithEachOther(&entity2,this->relationShip,&connector2);

	ASSERT_THROW(this->relationShip->canConnectTo(&Entity(ComponentData("7","NoteBook"))),InvalidConnectException);
}

TEST_F(RelationShipTest,testHasSizeToConnect){
	ASSERT_EQ(true,this->attribute->hasSizeToConnect());
	ASSERT_EQ(true,this->relationShip->hasSizeToConnect());
	ASSERT_EQ(true,this->entity->hasSizeToConnect());

	Connector connector1 = Connector(ComponentData("3",""));
	connectWithEachOther(this->relationShip,this->entity,&connector1);
	ASSERT_EQ(true,this->relationShip->hasSizeToConnect());

	Entity entity2 = Entity(ComponentData("4","NoteBook"));
	Connector connector2 = Connector(ComponentData("5",""));
	connectWithEachOther(this->relationShip,&entity2,&connector2);
	ASSERT_EQ(false,this->relationShip->hasSizeToConnect());
}

TEST_F(RelationShipTest,testIsRelationType){	
	ASSERT_EQ(false,this->relationShip->isRelationType("X"));
	
	ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::OneToOne));

	Connector connector1 = Connector(ComponentData("3",""));
	connectWithEachOther(this->relationShip,this->entity,&connector1);
	Entity entity2 = Entity(ComponentData("4","NoteBook"));
	Connector connector2 = Connector(ComponentData("5",""));
	connectWithEachOther(this->relationShip,&entity2,&connector2);
	ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::OneToOne));
	connector1.setName(RelationType::OneToOne);
	ASSERT_EQ(false,this->relationShip->isRelationType(RelationType::OneToOne));
	connector2.setName(RelationType::OneToOne);
	ASSERT_EQ(true,this->relationShip->isRelationType(RelationType::OneToOne));
}

TEST_F(RelationShipTest,testGetConnectedEntities){
	ASSERT_EQ(0,this->relationShip->getConnectedEntities().size());
	Connector connector1 = Connector(ComponentData("3",""));
	connectWithEachOther(this->relationShip,this->entity,&connector1);

	ASSERT_EQ(1,this->relationShip->getConnectedEntities().size());
	Entity entity2 = Entity(ComponentData("4","NoteBook"));
	Connector connector2 = Connector(ComponentData("5",""));
	connectWithEachOther(this->relationShip,&entity2,&connector2);
	ASSERT_EQ(2,this->relationShip->getConnectedEntities().size());	
}

TEST_F(RelationShipTest,testClone){
	RelationShip relationShipCloned = *static_cast<RelationShip*>(this->relationShip->clone());

	ASSERT_EQ(this->relationShip->getID(),relationShipCloned.getID());
	ASSERT_EQ(this->relationShip->getName(),relationShipCloned.getName());
	ASSERT_EQ(this->relationShip->getType(),relationShipCloned.getType());
	//assert componentData
	ASSERT_EQ(this->relationShip->componentData,relationShipCloned.componentData);
}