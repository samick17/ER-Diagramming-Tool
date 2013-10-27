#include "CommandMenuTest.h"
#include "OpenFileCommand.h"
#include "FindComponentCommand.h"
#include "NullPointerException.h"
#include "ERModel.h"
#include "Presentation.h"
#include "AddNodeCommand.h"
#include "CommandData.h"
#include "DuplicatedKeyException.h"

void CommandMenuTest::SetUp(){
}

void CommandMenuTest::TearDown(){	
}

TEST_F(CommandMenuTest,testGetCommandDataByKey){
	CommandData* commandData = this->commandMenu.getCommandDataByKey("1");
	ASSERT_EQ("1",commandData->getKey());
	ASSERT_THROW(this->commandMenu.getCommandDataByKey("0"),NullPointerException);
	ASSERT_THROW(this->commandMenu.getCommandDataByKey("12"),NullPointerException);
}

TEST_F(CommandMenuTest,testInsertCommandData){
	ASSERT_EQ(11,this->commandMenu.commandDataMap.size());
	CommandData* openFileCommandData = new CommandData("1","Load ER diagram file",CommandMenu::newCommand<OpenFileCommand>);
	ASSERT_THROW(this->commandMenu.insertCommandData(openFileCommandData),DuplicatedKeyException);	
	CommandData* findComponentCommand = new CommandData("13","Find Component",CommandMenu::newCommand<FindComponentCommand>);
	this->commandMenu.insertCommandData(findComponentCommand);
	ASSERT_EQ(12,this->commandMenu.commandDataMap.size());	
}

TEST_F(CommandMenuTest,testNewCommand){
	ERModel erModel;
	Presentation presentation(&erModel);
	Command* command = CommandMenu::newCommand<OpenFileCommand>(&presentation);
	ASSERT_EQ(typeid(OpenFileCommand).name(),typeid(*command).name());
	delete command;
}