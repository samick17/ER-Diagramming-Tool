#include "CommandData.h"

CommandData::CommandData(string key,string info,CommandInstruction commandInstruction) : key(key),info(info),commandInstruction(commandInstruction){
}

CommandData::~CommandData(){
}
//the key to trigger command
string CommandData::getKey(){
    return this->key;
}
//the information to describe this command
string CommandData::getInfo(){
    return this->info;
}
//the function pointer to new command instance
CommandInstruction CommandData::getCommandInstruction(){
    return this->commandInstruction;
}