#include "ComponentTest.h"
#include "ComponentType.h"

void ComponentTest::SetUp(){
	this->attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	this->relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	this->entity = this->erModel.addNode(ComponentType::TypeEntity);

	this->erModel.addConnection(this->attribute,this->entity);
	this->connector = this->erModel.getNodesConnector(this->attribute,this->entity);
}

void ComponentTest::TearDown(){
}

TEST_F(ComponentTest,testToString){
	ASSERT_EQ(ComponentType::TypeAttribute,this->attribute->Component::toString());
	ASSERT_EQ(ComponentType::TypeRelationShip,this->relationShip->Component::toString());
	ASSERT_EQ(ComponentType::TypeEntity,this->entity->Component::toString());
	ASSERT_EQ(ComponentType::TypeConnector,this->connector->Component::toString());

	this->attribute->setName("Name");
	ASSERT_EQ(ComponentType::TypeAttribute+", "+this->attribute->getName(),this->attribute->Component::toString());

	this->relationShip->setName("Has");
	ASSERT_EQ(ComponentType::TypeRelationShip+", "+this->relationShip->getName(),this->relationShip->Component::toString());

	this->entity->setName("Engineer");
	ASSERT_EQ(ComponentType::TypeEntity+", "+this->entity->getName(),this->entity->Component::toString());

	this->connector->setName("1");
	ASSERT_EQ(ComponentType::TypeConnector+", "+this->connector->getName(),this->connector->Component::toString());

}

TEST_F(ComponentTest,testGetClassName){
	ASSERT_EQ(ComponentType::TypeAttributeName,this->attribute->getClassName());
	ASSERT_EQ(ComponentType::TypeRelationShipName,this->relationShip->getClassName());
	ASSERT_EQ(ComponentType::TypeEntityName,this->entity->getClassName());
	ASSERT_EQ(ComponentType::TypeConnectorName,this->connector->getClassName());
}

TEST_F(ComponentTest,testConnectTo){
	ASSERT_EQ(1,this->attribute->getAllConnections().size());
	ASSERT_EQ(true,this->attribute->getAllConnections().containsKey("3"));
	
	this->attribute->connectTo(this->connector);
	ASSERT_EQ(1,this->attribute->getAllConnections().size());

	ASSERT_EQ(1,this->entity->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
	this->entity->connectTo(this->relationShip);
	ASSERT_EQ(2,this->entity->getAllConnections().size());
	ASSERT_EQ(0,this->relationShip->getAllConnections().size());
}

TEST_F(ComponentTest,testDisconnectTo){
	ASSERT_EQ(1,this->attribute->getAllConnections().size());
	ASSERT_EQ(true,this->attribute->getAllConnections().containsKey("3"));
	
	this->attribute->disconnectTo(this->entity);
	ASSERT_EQ(1,this->attribute->getAllConnections().size());

	this->attribute->disconnectTo(this->connector);
	ASSERT_EQ(0,this->attribute->getAllConnections().size());
}