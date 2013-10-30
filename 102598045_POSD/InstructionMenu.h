#pragma once

#include "InstructionData.h"
#include "HashMap.h"

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
    void insertInstructionData(InstructionData* instructionData);
};