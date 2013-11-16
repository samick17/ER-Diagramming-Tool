#include "InstructionData.h"
#include "TextInstruction.h"

InstructionData::InstructionData(string key,string info,NewInstructionFunction newInstructionFunction) : key(key),info(info),newInstructionFunction(newInstructionFunction){
}

InstructionData::~InstructionData(){
}
//the key to trigger command
string InstructionData::getKey(){
    return this->key;
}
//the information to describe this command
string InstructionData::getInfo(){
    return this->info;
}
//the function pointer to new command instance
NewInstructionFunction InstructionData::getNewInstructionFunction(){
    return this->newInstructionFunction;
}