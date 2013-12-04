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
    TextInstruction* createInstruction(string instructionKey);
private:
    template<typename Type>
    static TextInstruction* newTextInstruction();

    void insertInstructionData(InstructionData* instructionData);
    HashMap<string,InstructionData*> instructionDataMap;
    TextPresentation* textPresentation;
};

template<typename Type>
static TextInstruction* InstructionMenu::newTextInstruction(){
    return new Type();
}