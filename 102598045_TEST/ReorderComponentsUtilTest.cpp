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

TEST_F(ReorderComponentsUtilTest,testGetReorderedComponentMap){
	HashMap<string,Component*> orderedIDComponentMap = this->reorderComponentUtil.getReorderedComponentMap(&this->erModel);
	unsigned int index = 0;
	for each(Component* component in orderedIDComponentMap){
		ASSERT_EQ(StringUtil::intToString(index),component->getID());
		index++;
	}
}

TEST_F(ReorderComponentsUtilTest,testCloneComponentSet){	
	HashMap<string,Component*> componentMapCloned = this->reorderComponentUtil.cloneComponentMap(&this->erModel);
	ASSERT_EQ(this->erModel.getAllComponents().size(),componentMapCloned.size());
	for (unsigned int index = 0;index<componentMapCloned.size();index++){
		ASSERT_EQ(this->erModel.getAllComponents().getValueByIndex(index)->getID(),componentMapCloned.getValueByIndex(index)->getID());
		ASSERT_EQ(this->erModel.getAllComponents().getValueByIndex(index)->getName(),componentMapCloned.getValueByIndex(index)->getName());
	}
}

TEST_F(ReorderComponentsUtilTest,testClearComponentMap){
	ASSERT_EQ(0,this->reorderComponentUtil.componentMap.size());
	this->reorderComponentUtil.cloneComponentMap(&this->erModel);
	ASSERT_EQ(7,this->reorderComponentUtil.componentMap.size());
	this->reorderComponentUtil.clearComponentMap();
	ASSERT_EQ(0,this->reorderComponentUtil.componentMap.size());
}

TEST_F(ReorderComponentsUtilTest,testReorderClonedComponents){
	this->reorderComponentUtil.cloneComponentMap(&this->erModel);
	this->reorderComponentUtil.reConnectToComponentVector();
	
	queue<Component*> componentQueue;
	for each(Component* component in this->reorderComponentUtil.componentMap)
		componentQueue.push(component);
	HashMap<string,Component*> orderedIDComponentMap = this->reorderComponentUtil.dequeueAndInsertToVector(componentQueue);
	
	unsigned int index = 0;
	for each(Component* component in orderedIDComponentMap){
		ASSERT_EQ(StringUtil::intToString(index),component->getID());
		index++;
	}
}