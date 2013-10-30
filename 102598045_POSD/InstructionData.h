#pragma once

#include <string>
#include "InstructionMenu.h"
#include <gtest/gtest_prod.h> 

class TextInstruction;

using namespace std;

typedef TextInstruction* (*NewInstructionFunction)();

struct InstructionData{
public:
    InstructionData(string key,string info,NewInstructionFunction newInstructionFunction);
    ~InstructionData();

    string getKey();
    string getInfo();
    NewInstructionFunction getNewInstructionFunction();
private:
    string key;
    string info;
    NewInstructionFunction newInstructionFunction;
};