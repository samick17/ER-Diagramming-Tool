#include "CommandData.h"

CommandData::CommandData(string key,string info,NewCommandFunction newCommandFunction) : key(key),info(info),newCommandFunction(newCommandFunction){
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
NewCommandFunction CommandData::getNewCommandFunction(){
	return this->newCommandFunction;
}