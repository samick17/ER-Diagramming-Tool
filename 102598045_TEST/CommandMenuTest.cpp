#include "CommandMenuTest.h"
#include <iostream>
#include "LoadFileCommand.h"

void CommandMenuTest::SetUp(){
}

void CommandMenuTest::TearDown(){	
}

TEST_F(CommandMenuTest,testGetCommandDataByKey){
	CommandData* commandData = this->commandMenu.getCommandDataByKey("1");
	ASSERT_EQ("1",commandData->getKey());
}

TEST_F(CommandMenuTest,getCommandDataVector){	
}

TEST_F(CommandMenuTest,testInsertCommandData){
}

TEST_F(CommandMenuTest,NewCommand){
}