#include "AddNodeCommandTest.h"
#include "AddNodeCommand.h"
#include "EmptyCollectionException.h"
#include "ERModel.h"
#include "ComponentType.h"

void AddNodeCommandTest::SetUp(){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
}

void AddNodeCommandTest::TearDown(){
}

TEST_F(AddNodeCommandTest,testExecute){
    Node* entity = new Entity("0","Account");
    AddNodeCommand addNodeCommand = AddNodeCommand(&this->erModel,entity);

    addNodeCommand.execute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
    //execute again,it should have no change
    addNodeCommand.execute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
}

TEST_F(AddNodeCommandTest,testUnexecute){
    Node* attribute = new Attribute("0","Attribute");
    this->erModel.componentMap.put(attribute->getID(),attribute);
    AddNodeCommand addNodeCommand1 = AddNodeCommand(&this->erModel,attribute);
    addNodeCommand1.executionFlag = true;

    ASSERT_EQ(1,this->erModel.getAllComponents().size());

    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
    //unexecute again,it should have no change
    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
}

TEST_F(AddNodeCommandTest,testAddNodeCommand){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());

    Node* entity = new Entity("0","Account");
    AddNodeCommand addNodeCommand1 = AddNodeCommand(&this->erModel,entity);

    addNodeCommand1.execute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
    addNodeCommand1.execute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());

    
    Node* attribute = new Attribute("1","ID");
    AddNodeCommand addNodeCommand2 = AddNodeCommand(&this->erModel,attribute);

    addNodeCommand2.execute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());
    addNodeCommand2.unExecute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
    addNodeCommand2.execute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());
    addNodeCommand2.unExecute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());

    Node* relationShip = new RelationShip("2","Has");
    AddNodeCommand addNodeCommand3 = AddNodeCommand(&this->erModel,relationShip);

    addNodeCommand3.execute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());
    addNodeCommand3.unExecute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
    addNodeCommand3.execute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());
}