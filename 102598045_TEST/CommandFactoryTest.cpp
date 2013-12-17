#include "CommandFactoryTest.h"
#include "ERModel.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentsCommand.h"

void CommandFactoryTest::SetUp(){
}

void CommandFactoryTest::TearDown(){
}

TEST_F(CommandFactoryTest,testCreateAddNodeCommand){
    ERModel erModel;
    Node* attribute = new Attribute("testAttribute");
    Command* command = this->commandFactory.createAddNodeCommand(&erModel,attribute);
    ASSERT_EQ(typeid(AddNodeCommand).name(),typeid(*command).name());
    delete attribute;
}

TEST_F(CommandFactoryTest,testCreateConnectNodeCommand){
    ERModel erModel;
    Node* entity = new Entity("testEntity");
    Node* relationShip = new RelationShip("testRelationShip");
    Connector* connector = new Connector("testConnector");
    Command* command = this->commandFactory.createConnectNodeCommand(&erModel,entity,relationShip,connector);
    ASSERT_EQ(typeid(ConnectNodeCommand).name(),typeid(*command).name());
    delete entity;
    delete relationShip;
    delete connector;
}

TEST_F(CommandFactoryTest,testCreateDeleteComponentCommand){
    ERModel erModel;
    Attribute* attribute = new Attribute("testAttribute");

    vector<string> componentVector;
    componentVector.push_back(attribute->getID());
    Command* command = this->commandFactory.createDeleteComponentsCommand(&erModel,componentVector);
    ASSERT_EQ(typeid(DeleteComponentsCommand).name(),typeid(*command).name());
    delete attribute;
}