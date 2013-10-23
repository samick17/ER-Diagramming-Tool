#include "CommandManagerTest.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "ComponentType.h"
#include "EmptyCollectionException.h"
#include "ComponentFactory.h"

void CommandManagerTest::SetUp(){
	this->presentation = new Presentation(&erModel);
	this->commandManager = new CommandManager(presentation);	
}

void CommandManagerTest::TearDown(){
	delete this->presentation;
	delete this->commandManager;
}

TEST_F(CommandManagerTest,testCommandManager){
	ASSERT_EQ(0,this->erModel.getAllComponents().size());
	ASSERT_EQ(0,this->commandManager->undoCommandsStack.size());
	//execute "Add a node", add relationShip
	AddNodeCommand* addNodeCommand = new AddNodeCommand(this->presentation);
	Component* relationShip = new RelationShip(ComponentData("0","name"));
	addNodeCommand->node = relationShip;
	this->commandManager->execute(addNodeCommand);
	//assert size
	ASSERT_EQ(1,this->erModel.getAllComponents().size());
	ASSERT_EQ(1,this->commandManager->undoCommandsStack.size());
	ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
	//set id to '1'
	ComponentFactory::count = 1;	

	//execute "Connect two nodes", connect entity & attribute
	ConnectNodeCommand* connectNodeCommand = new ConnectNodeCommand(this->presentation);
	Component* entityTest = this->erModel.addNode(ComponentType::TypeEntity);
	ASSERT_EQ(2,this->erModel.getAllComponents().size());
	entityTest->setName("Test");

	Component* attributeTestAttr = this->erModel.addNode(ComponentType::TypeAttribute);
	ASSERT_EQ(3,this->erModel.getAllComponents().size());
	attributeTestAttr->setName("Test Attr");
	connectNodeCommand->firstNode = entityTest;
	connectNodeCommand->secondNode = attributeTestAttr;
	this->commandManager->execute(connectNodeCommand);
	//assert size
	ASSERT_EQ(4,this->erModel.getAllComponents().size());
	ASSERT_EQ(2,this->commandManager->undoCommandsStack.size());
	ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
	//execute "Delete component" ,delete entity
	DeleteComponentCommand* deleteEntityCommand = new DeleteComponentCommand(this->presentation);
	deleteEntityCommand->component = entityTest;
	this->commandManager->execute(deleteEntityCommand);
	ASSERT_EQ(2,this->erModel.getAllComponents().size());
	ASSERT_EQ(3,this->commandManager->undoCommandsStack.size());
	ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
	//undo & assert size
	this->commandManager->undo();
	ASSERT_EQ(4,this->erModel.getAllComponents().size());
	ASSERT_EQ(2,this->commandManager->undoCommandsStack.size());
	ASSERT_EQ(1,this->commandManager->redoCommandsStack.size());
	//execute delete command & assert size
	DeleteComponentCommand* deleteConnectorCommand = new DeleteComponentCommand(this->presentation);
	deleteConnectorCommand->component = this->erModel.getComponentByID("3");
	this->commandManager->execute(deleteConnectorCommand);
	ASSERT_EQ(3,this->erModel.getAllComponents().size());
	ASSERT_EQ(3,this->commandManager->undoCommandsStack.size());
	ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
}