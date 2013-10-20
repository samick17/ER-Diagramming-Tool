#include "EntityTest.h"
#include "ComponentType.h"
#include "InvalidConnectException.h"
#include "ConnectedSelfException.h"
#include "HasConnectedException.h"

void EntityTest::SetUp(){
	this->attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	this->relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	this->entity = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
}

void EntityTest::TearDown(){
}

TEST_F(EntityTest,testToString){
}

TEST_F(EntityTest,testGetType){
}

TEST_F(EntityTest,testCanConnectTo){
}

TEST_F(EntityTest,testGetConnectedAttributes){
}

TEST_F(EntityTest,testGetAttributeByID){
}

TEST_F(EntityTest,testGetPrimaryKeyAttributes){
}

TEST_F(EntityTest,testSetPrimaryKey){
}