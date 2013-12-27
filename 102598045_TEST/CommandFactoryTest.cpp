#include "CommandFactoryTest.h"
#include "ERModel.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteMultiComponentCommand.h"

void CommandFactoryTest::SetUp(){
}

void CommandFactoryTest::TearDown(){
}

TEST_F(CommandFactoryTest,testCreateAddNodeCommand){
    ERModel erModel;
    Node* attribute = new Attribute("testAttribute");
    HashMap<string,Component*> componentMap;
    Command* command = this->commandFactory.createAddNodeCommand(componentMap,attribute);
    ASSERT_EQ(typeid(AddNodeCommand).name(),typeid(*command).name());
    delete attribute;
}

TEST_F(CommandFactoryTest,testCreateConnectNodeCommand){
    ERModel erModel;
    Node* entity = new Entity("testEntity");
    Node* relationShip = new RelationShip("testRelationShip");
    Connector* connector = new Connector("testConnector");
    HashMap<string,Component*> componentMap;
    Command* command = this->commandFactory.createConnectNodeCommand(componentMap,entity,relationShip,connector);
    ASSERT_EQ(typeid(ConnectNodeCommand).name(),typeid(*command).name());
    delete entity;
    delete relationShip;
    delete connector;
}

TEST_F(CommandFactoryTest,testCreateDeleteComponentCommand){
    ERModel erModel;
    Attribute* attribute = new Attribute("testAttribute");

    HashMap<string,Component*> componentMap;
    Command* command = this->commandFactory.createDeleteMultiComponentCommand(componentMap,componentMap);
    ASSERT_EQ(typeid(DeleteMultiComponentCommand).name(),typeid(*command).name());
    delete attribute;
}