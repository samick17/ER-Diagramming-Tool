#include "AddNodeCommandTest.h"
#include "AddNodeCommand.h"
#include "EmptyCollectionException.h"
#include "Component.h"
#include "Entity.h"
#include "RelationShip.h"
#include "ComponentType.h"

void AddNodeCommandTest::SetUp(){
}

void AddNodeCommandTest::TearDown(){
    for each(Component* component in this->componentMap){
        delete component;
    }
    this->componentMap.clear();
}

TEST_F(AddNodeCommandTest,testExecute){
    Node* entity = new Entity("0","Account");
    AddNodeCommand addNodeCommand = AddNodeCommand(this->componentMap,entity);

    addNodeCommand.execute();
    ASSERT_EQ(1,this->componentMap.size());
    //execute again,it should have no change
    addNodeCommand.execute();
    ASSERT_EQ(1,this->componentMap.size());
}

TEST_F(AddNodeCommandTest,testUnexecute){
    Node* attribute = new Attribute("0","Attribute");
    this->componentMap.put(attribute->getID(),attribute);
    AddNodeCommand addNodeCommand1 = AddNodeCommand(this->componentMap,attribute);
    addNodeCommand1.executionFlag = true;

    ASSERT_EQ(1,this->componentMap.size());

    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->componentMap.size());
    //unexecute again,it should have no change
    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->componentMap.size());
}

TEST_F(AddNodeCommandTest,testAddNodeCommand){
    ASSERT_EQ(0,this->componentMap.size());

    Node* entity = new Entity("0","Account");
    AddNodeCommand addNodeCommand1 = AddNodeCommand(this->componentMap,entity);

    addNodeCommand1.execute();
    ASSERT_EQ(1,this->componentMap.size());
    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->componentMap.size());
    addNodeCommand1.execute();
    ASSERT_EQ(1,this->componentMap.size());

    Node* attribute = new Attribute("1","ID");
    AddNodeCommand addNodeCommand2 = AddNodeCommand(this->componentMap,attribute);

    addNodeCommand2.execute();
    ASSERT_EQ(2,this->componentMap.size());
    addNodeCommand2.unExecute();
    ASSERT_EQ(1,this->componentMap.size());
    addNodeCommand2.execute();
    ASSERT_EQ(2,this->componentMap.size());
    addNodeCommand2.unExecute();
    ASSERT_EQ(1,this->componentMap.size());

    Node* relationShip = new RelationShip("2","Has");
    AddNodeCommand addNodeCommand3 = AddNodeCommand(this->componentMap,relationShip);

    addNodeCommand3.execute();
    ASSERT_EQ(2,this->componentMap.size());
    addNodeCommand3.unExecute();
    ASSERT_EQ(1,this->componentMap.size());
    addNodeCommand3.execute();
    ASSERT_EQ(2,this->componentMap.size());
}