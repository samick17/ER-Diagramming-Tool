#include "ConnectNodeCommandTest.h"
#include "ConnectNodeCommand.h"
#include "ComponentType.h"

void ConnectNodeCommandTest::SetUp(){
	this->presentation = new Presentation(&erModel);
	this->erModel.addNode(ComponentType::TypeEntity);
	this->erModel.addNode(ComponentType::TypeAttribute);
	this->erModel.addNode(ComponentType::TypeRelationShip);
}

void ConnectNodeCommandTest::TearDown(){
	delete this->presentation;
}

TEST_F(ConnectNodeCommandTest,testConnectNodeCommand){
	ASSERT_EQ(3,this->erModel.getAllComponents().size());
	ConnectNodeCommand connectNodeCommand1 = ConnectNodeCommand(this->presentation);
	connectNodeCommand1.firstNode = this->erModel.getComponentByID("0");
	connectNodeCommand1.secondNode = this->erModel.getComponentByID("1");

	connectNodeCommand1.execute();
	ASSERT_EQ(1,connectNodeCommand1.firstNode->getAllConnections().size());
	ASSERT_EQ(1,connectNodeCommand1.secondNode->getAllConnections().size());
	ASSERT_EQ(true,connectNodeCommand1.firstNode->hasConnectedTo(connectNodeCommand1.secondNode));
	ASSERT_EQ(true,connectNodeCommand1.secondNode->hasConnectedTo(connectNodeCommand1.firstNode));
	ASSERT_EQ(4,this->erModel.getAllComponents().size());
	connectNodeCommand1.unExecute();
	ASSERT_EQ(0,connectNodeCommand1.firstNode->getAllConnections().size());
	ASSERT_EQ(0,connectNodeCommand1.secondNode->getAllConnections().size());
	ASSERT_EQ(false,connectNodeCommand1.firstNode->hasConnectedTo(connectNodeCommand1.secondNode));
	ASSERT_EQ(false,connectNodeCommand1.secondNode->hasConnectedTo(connectNodeCommand1.firstNode));
	ASSERT_EQ(3,this->erModel.getAllComponents().size());
	connectNodeCommand1.execute();
	ASSERT_EQ(1,connectNodeCommand1.firstNode->getAllConnections().size());
	ASSERT_EQ(1,connectNodeCommand1.secondNode->getAllConnections().size());
	ASSERT_EQ(true,connectNodeCommand1.firstNode->hasConnectedTo(connectNodeCommand1.secondNode));
	ASSERT_EQ(true,connectNodeCommand1.secondNode->hasConnectedTo(connectNodeCommand1.firstNode));
	ASSERT_EQ(4,this->erModel.getAllComponents().size());

	ConnectNodeCommand connectNodeCommand2 = ConnectNodeCommand(this->presentation);
	connectNodeCommand2.firstNode = this->erModel.getComponentByID("0");
	connectNodeCommand2.secondNode = this->erModel.getComponentByID("2");

	connectNodeCommand2.execute();
	ASSERT_EQ(2,connectNodeCommand2.firstNode->getAllConnections().size());
	ASSERT_EQ(1,connectNodeCommand2.secondNode->getAllConnections().size());
	ASSERT_EQ(true,connectNodeCommand2.firstNode->hasConnectedTo(connectNodeCommand2.secondNode));
	ASSERT_EQ(true,connectNodeCommand2.secondNode->hasConnectedTo(connectNodeCommand2.firstNode));
	ASSERT_EQ(5,this->erModel.getAllComponents().size());
	connectNodeCommand2.unExecute();
	ASSERT_EQ(1,connectNodeCommand2.firstNode->getAllConnections().size());
	ASSERT_EQ(0,connectNodeCommand2.secondNode->getAllConnections().size());
	ASSERT_EQ(false,connectNodeCommand2.firstNode->hasConnectedTo(connectNodeCommand2.secondNode));
	ASSERT_EQ(false,connectNodeCommand2.secondNode->hasConnectedTo(connectNodeCommand2.firstNode));
	ASSERT_EQ(4,this->erModel.getAllComponents().size());
	connectNodeCommand2.execute();
	ASSERT_EQ(2,connectNodeCommand2.firstNode->getAllConnections().size());
	ASSERT_EQ(1,connectNodeCommand2.secondNode->getAllConnections().size());
	ASSERT_EQ(true,connectNodeCommand2.firstNode->hasConnectedTo(connectNodeCommand2.secondNode));
	ASSERT_EQ(true,connectNodeCommand2.secondNode->hasConnectedTo(connectNodeCommand2.firstNode));
	ASSERT_EQ(5,this->erModel.getAllComponents().size());
}

TEST_F(ConnectNodeCommandTest,testBackupConnector){
	ConnectNodeCommand connectNodeCommand1 = ConnectNodeCommand(this->presentation);
	Component* entity = this->erModel.getComponentByID("0");
	Component* attribute = this->erModel.getComponentByID("1");	
	this->erModel.addConnection(entity,attribute);
	Component* connector1 = this->erModel.getComponentByID("3");

	connectNodeCommand1.backupConnector(entity,attribute);
	ASSERT_EQ(entity,connectNodeCommand1.firstNode);
	ASSERT_EQ(attribute,connectNodeCommand1.secondNode);
	ASSERT_EQ(connector1,connectNodeCommand1.connector);
	connectNodeCommand1.UnexecutableCommand::execute();

	ASSERT_EQ(4,this->erModel.getAllComponents().size());

	ConnectNodeCommand connectNodeCommand2 = ConnectNodeCommand(this->presentation);
	Component* relationShip = this->erModel.getComponentByID("2");	
	this->erModel.addConnection(entity,relationShip);
	Component* connector2 = this->erModel.getComponentByID("4");

	connectNodeCommand2.backupConnector(relationShip,entity);
	ASSERT_EQ(relationShip,connectNodeCommand2.firstNode);
	ASSERT_EQ(entity,connectNodeCommand2.secondNode);
	ASSERT_EQ(connector2,connectNodeCommand2.connector);	
	connectNodeCommand2.UnexecutableCommand::execute();

	ASSERT_EQ(5,this->erModel.getAllComponents().size());
}