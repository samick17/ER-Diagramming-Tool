#include "InstructionMenuTest.h"
#include "NullPointerException.h"
#include "ERModel.h"
#include "TextPresentation.h"
#include "AddNodeCommand.h"
#include "InstructionData.h"
#include "DuplicatedKeyException.h"

void InstructionMenuTest::SetUp(){
}

void InstructionMenuTest::TearDown(){
}

TEST_F(InstructionMenuTest,testGetInstructionDataByKey){
	InstructionData* instructionData = this->instructionMenu.getInstructionDataByKey("1");
    ASSERT_EQ("1",instructionData->getKey());
	ASSERT_THROW(this->instructionMenu.getInstructionDataByKey("0"),NullPointerException);
	ASSERT_THROW(this->instructionMenu.getInstructionDataByKey("12"),NullPointerException);
}

TEST_F(InstructionMenuTest,testInsertInstructionData){
	ASSERT_EQ(11,this->instructionMenu.instructionDataMap.size());
    InstructionData* openFileInstructionData = new InstructionData("1","Load ER diagram file",&TextPresentation::openFile);
	ASSERT_THROW(this->instructionMenu.insertInstructionData(openFileInstructionData),DuplicatedKeyException);
    InstructionData* findComponentInstructionData = new InstructionData("13","Find Component",&TextPresentation::openFile);
	this->instructionMenu.insertInstructionData(findComponentInstructionData);
	ASSERT_EQ(12,this->instructionMenu.instructionDataMap.size());
}