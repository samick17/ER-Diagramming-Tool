#include "CommandTest.h"

void CommandTest::SetUp(){
}

void CommandTest::TearDown(){
}

TEST_F(CommandTest,testExecute){
    this->mockCommand.execute();
    ASSERT_EQ(1,this->mockCommand.getExecutionValue());
    ASSERT_EQ(true,this->mockCommand.executionFlag);
    this->mockCommand.execute();
    ASSERT_EQ(1,this->mockCommand.getExecutionValue());
    ASSERT_EQ(true,this->mockCommand.executionFlag);
}

TEST_F(CommandTest,testUnExecute){
    this->mockCommand.executionFlag = true;
    this->mockCommand.unExecute();
    ASSERT_EQ(-1,this->mockCommand.getExecutionValue());
    ASSERT_EQ(false,this->mockCommand.executionFlag);
    this->mockCommand.unExecute();
    ASSERT_EQ(-1,this->mockCommand.getExecutionValue());
    ASSERT_EQ(false,this->mockCommand.executionFlag);
}