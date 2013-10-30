#pragma once

#include <string>
#include "TextPresentation.h"

using namespace std;

typedef void (TextPresentation::*TextInstruction)();

struct InstructionData{
public:
    InstructionData(string key,string info,TextInstruction textInstruction);
    ~InstructionData();

    string getKey();
    string getInfo();
    TextInstruction getTextInstruction();
private:
    string key;
    string info;
    TextInstruction textInstruction;
};