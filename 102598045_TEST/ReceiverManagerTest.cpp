#include "ReceiverManagerTest.h"
#include "ConnectedERReceiver.h"
#include "ValidConnectedReceiver.h"
#include "ComponentType.h"

void ReceiverManagerTest::SetUp(){
	ASSERT_EQ(0,this->receiverManager.receiverMap.size());
	this->presentation = new Presentation(&this->erModel);
	Component* attribute = this->erModel.addNode(ComponentType::TypeAttribute);
	Component* entity = this->erModel.addNode(ComponentType::TypeEntity);	
	this->receiverManager.insertReceiver(new ValidConnectedReceiver(0,this->presentation,entity,attribute));
	ASSERT_EQ(1,this->receiverManager.receiverMap.size());
}

void ReceiverManagerTest::TearDown(){
	delete this->presentation;
}

TEST_F(ReceiverManagerTest,testInsertReceiver){
	Component* relationShip = this->erModel.addNode(ComponentType::TypeRelationShip);
	Component* entity = this->erModel.addNode(ComponentType::TypeEntity);	
	Receiver* receiver = new ConnectedERReceiver(2,this->presentation,entity,relationShip);
	this->receiverManager.insertReceiver(receiver);
	ASSERT_EQ(2,this->receiverManager.receiverMap.size());
	ASSERT_EQ(receiver,this->receiverManager.receiverMap.get(2));
}

TEST_F(ReceiverManagerTest,testDeleteReceiver){
	this->receiverManager.deleteReceiver(this->receiverManager.receiverMap.get(0));
	ASSERT_EQ(0,this->receiverManager.receiverMap.size());
}