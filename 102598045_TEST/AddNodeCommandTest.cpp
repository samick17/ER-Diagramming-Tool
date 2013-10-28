#include "AddNodeCommandTest.h"
#include "AddNodeCommand.h"
#include "EmptyCollectionException.h"

void AddNodeCommandTest::SetUp(){
    this->textPresentation = new TextPresentation(&erModel);
}

void AddNodeCommandTest::TearDown(){
    delete this->textPresentation;
}

TEST_F(AddNodeCommandTest,testAddNodeCommand){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());

    Node* entity = new Entity(ComponentData("0","Account"));
	AddNodeCommand addNodeCommand1 = AddNodeCommand(&this->erModel,entity);

    addNodeCommand1.execute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
    addNodeCommand1.unExecute();
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
    addNodeCommand1.execute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());

    
    Node* attribute = new Attribute(ComponentData("1","ID"));
    AddNodeCommand addNodeCommand2 = AddNodeCommand(&this->erModel,attribute);

    addNodeCommand2.execute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());
    addNodeCommand2.unExecute();
    ASSERT_EQ(1,this->erModel.getAllComponents().size());
    addNodeCommand2.execute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());

    Node* relationShip = new RelationShip(ComponentData("2","Has"));
	AddNodeCommand addNodeCommand3 = AddNodeCommand(&this->erModel,relationShip);

    addNodeCommand3.execute();
    ASSERT_EQ(3,this->erModel.getAllComponents().size());
    addNodeCommand3.unExecute();
    ASSERT_EQ(2,this->erModel.getAllComponents().size());
    addNodeCommand3.execute();
    ASSERT_EQ(3,this->erModel.getAllComponents().size());
}