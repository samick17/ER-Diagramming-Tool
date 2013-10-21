#include "NodeTest.h"
#include "ComponentType.h"
#include "ConnectedSelfException.h"
#include "InvalidConnectException.h"
#include "HasConnectedException.h"

void NodeTest::SetUp(){
	this->attribute = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
	this->relationShip = static_cast<RelationShip*>(this->erModel.addNode(ComponentType::TypeRelationShip));
	this->entity = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
}

TEST_F(NodeTest,testBreakAllConnections){
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	ASSERT_EQ(0,this->entity->getAllConnections().size());

	this->erModel.addConnection(this->attribute,this->entity);
	this->erModel.addConnection(this->relationShip,this->entity);

	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	Component* attribute2 = this->erModel.addNode(ComponentType::TypeAttribute);
	this->erModel.addConnection(attribute2,this->entity);
	this->erModel.addConnection(this->relationShip,entity2);

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
	ASSERT_THROW(this->attribute->canConnectTo(this->erModel.addNode(ComponentType::TypeAttribute)),InvalidConnectException);
	ASSERT_THROW(this->entity->canConnectTo(this->erModel.addNode(ComponentType::TypeEntity)),InvalidConnectException);
	ASSERT_THROW(this->relationShip->canConnectTo(this->erModel.addNode(ComponentType::TypeRelationShip)),InvalidConnectException);

	this->erModel.addConnection(this->attribute,this->entity);
	this->erModel.addConnection(this->relationShip,this->entity);
	//has connected
	ASSERT_THROW(this->attribute->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->attribute),HasConnectedException);
	ASSERT_THROW(this->relationShip->canConnectTo(this->entity),HasConnectedException);
	ASSERT_THROW(this->entity->canConnectTo(this->relationShip),HasConnectedException);

	ASSERT_THROW(this->attribute->canConnectTo(this->erModel.addNode(ComponentType::TypeEntity)),InvalidConnectException);

	Component* entity2 = this->erModel.addNode(ComponentType::TypeEntity);
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->relationShip->canConnectTo(entity2));

	this->erModel.addConnection(entity2,this->relationShip);
	ASSERT_THROW(this->relationShip->canConnectTo(this->erModel.addNode(ComponentType::TypeEntity)),InvalidConnectException);

	ASSERT_EQ(NodeConnectionType::ValidConnect,this->entity->canConnectTo(this->erModel.addNode(ComponentType::TypeAttribute)));
	ASSERT_EQ(NodeConnectionType::ConnectEntityAndRelation,this->entity->canConnectTo(this->erModel.addNode(ComponentType::TypeRelationShip)));
}