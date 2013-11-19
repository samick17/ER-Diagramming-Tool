#include "ConnectNodeCommandTest.h"
#include "ConnectNodeCommand.h"
#include "ComponentType.h"

void ConnectNodeCommandTest::SetUp(){
	this->presentation = new Presentation(&this->erModel);
    this->textPresentation = new TextPresentation(this->presentation);
    this->entity = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    this->attribute = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    this->relationShip = static_cast<RelationShip*>(this->erModel.addNode(ComponentType::TypeRelationShip));
    ASSERT_EQ(3,this->erModel.getAllComponents().size());
}

void ConnectNodeCommandTest::TearDown(){
	delete this->presentation;
    delete this->textPresentation;
}

TEST_F(ConnectNodeCommandTest,testConnectNodeCommand){
	Connector* connector1 = new Connector("3");
	ConnectNodeCommand connectNodeCommand1 = ConnectNodeCommand(&this->erModel,this->entity,this->attribute,connector1);

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

	Connector* connector2 = new Connector("4");
	ConnectNodeCommand connectNodeCommand2 = ConnectNodeCommand(&this->erModel,this->entity,this->relationShip,connector2);

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