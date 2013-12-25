#include "ConnectNodeCommandTest.h"
#include "ConnectNodeCommand.h"
#include "ComponentType.h"

void ConnectNodeCommandTest::SetUp(){
    this->entity = static_cast<Entity*>(this->erModel.addNode(ComponentType::TypeEntity));
    this->attribute = static_cast<Attribute*>(this->erModel.addNode(ComponentType::TypeAttribute));
    this->relationShip = static_cast<RelationShip*>(this->erModel.addNode(ComponentType::TypeRelationShip));
    ASSERT_EQ(3,this->erModel.getAllComponents().size());
}

void ConnectNodeCommandTest::TearDown(){
}


TEST_F(ConnectNodeCommandTest,testExecute){
    Connector* connector1 = new Connector("3");
    ConnectNodeCommand connectNodeCommand = ConnectNodeCommand(this->erModel.componentMap,this->entity,this->attribute,connector1);

    connectNodeCommand.execute();
    ASSERT_EQ(1,connectNodeCommand.firstNode->getAllConnections().size());
    ASSERT_EQ(1,connectNodeCommand.secondNode->getAllConnections().size());
    ASSERT_EQ(true,connectNodeCommand.firstNode->hasConnectedTo(connectNodeCommand.secondNode));
    ASSERT_EQ(true,connectNodeCommand.secondNode->hasConnectedTo(connectNodeCommand.firstNode));
    ASSERT_EQ(4,this->erModel.getAllComponents().size());
    //execute again,it should be no change
    connectNodeCommand.execute();
    ASSERT_EQ(1,connectNodeCommand.firstNode->getAllConnections().size());
    ASSERT_EQ(1,connectNodeCommand.secondNode->getAllConnections().size());
    ASSERT_EQ(true,connectNodeCommand.firstNode->hasConnectedTo(connectNodeCommand.secondNode));
    ASSERT_EQ(true,connectNodeCommand.secondNode->hasConnectedTo(connectNodeCommand.firstNode));
    ASSERT_EQ(4,this->erModel.getAllComponents().size());
}

TEST_F(ConnectNodeCommandTest,testUnexecute){
    Connector* connector1 = new Connector("3");
    ConnectNodeCommand connectNodeCommand = ConnectNodeCommand(this->erModel.componentMap,this->entity,this->attribute,connector1);
    connectNodeCommand.executionFlag = true;

    //pretent to execute
    this->erModel.componentMap.put(connector1->getID(),connector1);
    this->entity->connectTo(connector1);
    this->attribute->connectTo(connector1);
    connector1->connectTo(entity);
    connector1->connectTo(attribute);
    //ASSERT
    ASSERT_EQ(1,connectNodeCommand.firstNode->getAllConnections().size());
    ASSERT_EQ(1,connectNodeCommand.secondNode->getAllConnections().size());
    ASSERT_EQ(true,connectNodeCommand.firstNode->hasConnectedTo(connectNodeCommand.secondNode));
    ASSERT_EQ(true,connectNodeCommand.secondNode->hasConnectedTo(connectNodeCommand.firstNode));
    ASSERT_EQ(4,this->erModel.componentMap.size());
    //test for unexecute

    connectNodeCommand.unExecute();
    ASSERT_EQ(0,connectNodeCommand.firstNode->getAllConnections().size());
    ASSERT_EQ(0,connectNodeCommand.secondNode->getAllConnections().size());
    ASSERT_EQ(false,connectNodeCommand.firstNode->hasConnectedTo(connectNodeCommand.secondNode));
    ASSERT_EQ(false,connectNodeCommand.secondNode->hasConnectedTo(connectNodeCommand.firstNode));
    ASSERT_EQ(3,this->erModel.componentMap.size());
    //unexecute again it should be no change
    connectNodeCommand.unExecute();
    ASSERT_EQ(0,connectNodeCommand.firstNode->getAllConnections().size());
    ASSERT_EQ(0,connectNodeCommand.secondNode->getAllConnections().size());
    ASSERT_EQ(false,connectNodeCommand.firstNode->hasConnectedTo(connectNodeCommand.secondNode));
    ASSERT_EQ(false,connectNodeCommand.secondNode->hasConnectedTo(connectNodeCommand.firstNode));
    ASSERT_EQ(3,this->erModel.componentMap.size());
}

TEST_F(ConnectNodeCommandTest,testConnectNodeCommand){
    Connector* connector1 = new Connector("3");
    ConnectNodeCommand connectNodeCommand1 = ConnectNodeCommand(this->erModel.componentMap,this->entity,this->attribute,connector1);

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
    ConnectNodeCommand connectNodeCommand2 = ConnectNodeCommand(this->erModel.componentMap,this->entity,this->relationShip,connector2);

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