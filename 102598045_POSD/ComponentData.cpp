#include "ComponentData.h"

ComponentData::ComponentData(string id,string name) : id(id),name(name){
}

ComponentData::~ComponentData(){
}

string ComponentData::getID(){
    return this->id;
}

void ComponentData::setID(string id){
    this->id = id;
}

string ComponentData::getName(){
    return this->name;
}

void ComponentData::setName(string name){
    this->name = name;
}

bool ComponentData::operator==(const ComponentData& componentDataToCompare) const{
    if(this->id == componentDataToCompare.id && this->name == componentDataToCompare.name){
        return true;
    }
    return false;
}