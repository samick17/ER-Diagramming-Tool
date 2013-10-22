#include "NodeTest.h"
#include "ComponentType.h"
#include "ConnectedSelfException.h"
#include "InvalidConnectException.h"
#include "HasConnectedException.h"

void NodeTest::SetUp(){
	this->attribute = new Attribute(ComponentData("0","Name"));
	this->relationShip = new RelationShip(ComponentData("1","Has"));
	this->entity = new Entity(ComponentData("2","Engineer"));
}

void NodeTest::TearDown(){
	delete this->attribute;
	delete this->relationShip;
	delete this->entity;
}

TEST_F(NodeTest,testBreakAllConnections){
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());

	Connector connector1 = Connector(ComponentData("3",""));
	connectWithEachOther(this->attribute,this->entity,&connector1);
	Connector connector2 = Connector(ComponentData("4",""));
	connectWithEachOther(this->relationShip,this->entity,&connector2);

	Entity entity2 = Entity(ComponentData("5",""));
	Attribute attribute2 = Attribute(ComponentData("6",""));
	Connector connector3 = Connector(ComponentData("7",""));
	connectWithEachOther(&attribute2,this->entity,&connector3);
	Connector connector4 = Connector(ComponentData("8",""));
	connectWithEachOther(this->relationShip,&entity2,&connector4);

	ASSERT_EQ(1,this->attribute->getAllConnections().size());
	ASSERT_EQ(2,this->relationShip->getAllConnections().size());
	ASSERT_EQ(3,this->entity->getAllConnections().size());

	this->attribute->breakAllConnections();
	this->relationShip->breakAllConnections();
	this->entity->breakAllConnections();

	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());
}

TEST_F(NodeTest,testCanConnectTo){
	//connect self
	ASSERT_THROW(this->attribute->canConnectTo(this->attribute),ConnectedSelfException);
	ASSERT_THROW(this->entity->canConnectTo(this->entity),ConnectedSelfException);
	ASSERT_THROW(this->relationShip->canConnectTo(this->relationShip),ConnectedSelfException);
	//same type
	ASSERT_THROW(this->attribute->canConnectTo(&Attribute(ComponentData("3",""))),InvalidConnectException);
	ASSERT_THROW(this->entity->canConnectTo(&Entity(ComponentData("4",""))),InvalidConnectException);
	ASSERT_THROW(this->relationShip->canConnectTo(&RelationShip(ComponentData("5",""))),InvalidConnectException);

	Connector connector1 = Connector(ComponentData("3",""));
	connectWithEachOther(this->attribute,this->entity,&connector1);
	Connector connector2 = Connector(ComponentData("4",""));
	connectWithEachOther(this->relationShip,this->entity,&connector2);
	//has connected
	ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
	ASSERT_THROW(this->relationShip->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->relationShip),HasConnectedException);

	ASSERT_THROW(this->attribute->canConnectTo(&Entity(ComponentData("6",""))),InvalidConnectException);

	Entity entity2 = Entity(ComponentData("7",""));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->relationShip->canConnectTo(&entity2));

	Connector connector3 = Connector(ComponentData("8",""));
	connectWithEachOther(&entity2,this->relationShip,&connector3);	
	ASSERT_THROW(this->relationShip->canConnectTo(&Entity(ComponentData("9",""))),InvalidConnectException);

	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(&Attribute(ComponentData("10",""))));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(&RelationShip(ComponentData("11",""))));
}