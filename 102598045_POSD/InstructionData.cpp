#include "InstructionData.h"

InstructionData::InstructionData(string key,string info,TextInstruction textInstruction) : key(key),info(info),textInstruction(textInstruction){
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
TextInstruction InstructionData::getTextInstruction(){
    return this->textInstruction;
}