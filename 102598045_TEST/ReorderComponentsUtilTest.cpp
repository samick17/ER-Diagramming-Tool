#include "ReorderComponentsUtilTest.h"
#include "ComponentType.h"
#include "StringUtil.h"

void ReorderComponentsUtilTest::SetUp(){
	Component* component1 = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* component2 = this->erModel.addNode(ComponentType::TypeEntity);
	Component* component3 = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* component4 = this->erModel.addNode(ComponentType::TypeRelationShip);
	this->erModel.addConnection(this->erModel.getComponentByID("0"),this->erModel.getComponentByID("1"));
	this->erModel.addConnection(this->erModel.getComponentByID("2"),this->erModel.getComponentByID("1"));
	this->erModel.addConnection(this->erModel.getComponentByID("1"),this->erModel.getComponentByID("3"));
	component1->setID("20");
	component2->setID("12");
	component3->setID("57");
	component4->setID("36");
}

void ReorderComponentsUtilTest::TearDown(){
}

TEST_F(ReorderComponentsUtilTest,testGetReorderedComponentIDMap){
	
}