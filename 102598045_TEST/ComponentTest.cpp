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
	
}

TEST_F(ComponentTest,testGetClassName){
}

TEST_F(ComponentTest,testConnectTo){
}

TEST_F(ComponentTest,testDisconnectTo){
}