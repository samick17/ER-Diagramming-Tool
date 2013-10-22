#include "AddNodeCommandTest.h"
#include "AddNodeCommand.h"
#include "EmptyCollectionException.h"

void AddNodeCommandTest::SetUp(){
	this->presentation = new Presentation(&erModel);
}

void AddNodeCommandTest::TearDown(){
	delete this->presentation;
}

TEST_F(AddNodeCommandTest,testAddNodeCommand){
	ASSERT_THROW(this->erModel.getAllComponents(),EmptyCollectionException);

	AddNodeCommand addNodeCommand1 = AddNodeCommand(this->presentation);	
	Component* entity = new Entity(ComponentData("0","Account"));
	addNodeCommand1.node = entity;

	addNodeCommand1.execute();
	ASSERT_EQ(1,this->erModel.getAllComponents().size());
	addNodeCommand1.unExecute();
	ASSERT_THROW(this->erModel.getAllComponents(),EmptyCollectionException);
	addNodeCommand1.execute();
	ASSERT_EQ(1,this->erModel.getAllComponents().size());

	AddNodeCommand addNodeCommand2 = AddNodeCommand(this->presentation);	
	Component* attribute = new Attribute(ComponentData("1","ID"));
	addNodeCommand2.node = attribute;

	addNodeCommand2.execute();
	ASSERT_EQ(2,this->erModel.getAllComponents().size());
	addNodeCommand2.unExecute();
	ASSERT_EQ(1,this->erModel.getAllComponents().size());
	addNodeCommand2.execute();
	ASSERT_EQ(2,this->erModel.getAllComponents().size());

	AddNodeCommand addNodeCommand3 = AddNodeCommand(this->presentation);	
	Component* relationShip = new RelationShip(ComponentData("2","Has"));
	addNodeCommand3.node = relationShip;

	addNodeCommand3.execute();
	ASSERT_EQ(3,this->erModel.getAllComponents().size());
	addNodeCommand3.unExecute();
	ASSERT_EQ(2,this->erModel.getAllComponents().size());
	addNodeCommand3.execute();
	ASSERT_EQ(3,this->erModel.getAllComponents().size());
}