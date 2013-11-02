#pragma once

#include "HashMap.h"
#include "TextPresentation.h"
#include "TextInstruction.h"
#include <gtest/gtest_prod.h> 

struct InstructionData;

class InstructionMenu{
    friend class InstructionMenuTest;
    FRIEND_TEST(InstructionMenuTest,testInsertInstructionData);
public:
    InstructionMenu();
    ~InstructionMenu();

    HashMap<string,InstructionData*> getInstructionDataMap();
    InstructionData* getInstructionDataByKey(string key);
private:
    HashMap<string,InstructionData*> instructionDataMap;
	TextPresentation* textPresentation;
    void insertInstructionData(InstructionData* instructionData);
	
	template<typename Type>
	static TextInstruction* newTextInstruction();
};

template<typename Type>
static TextInstruction* InstructionMenu::newTextInstruction(){
	return new Type();
}