#include "ComponentData.h"
#include "Number.h"
#include "ComponentType.h"

ComponentData::ComponentData(string type,string id,string name) : type(type),id(id),name(name){
    this->isUnderLine = false;
    this->className = ComponentType::getClassName(type);
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

string ComponentData::getType(){
    return this->type;
}

string ComponentData::getClassName(){
    return this->className;
}

bool ComponentData::getIsUnderLine(){
    return this->isUnderLine;
}

void ComponentData::setIsUnderLine(bool isUnderLine){
    this->isUnderLine = isUnderLine;
}

Rect ComponentData::getRect(){
    return this->rect;
}

void ComponentData::setPosition(Point position){
    this->rect.setPosition(position);
}

void ComponentData::setCenterPosition(Point position){
    this->rect.setCenterPosition(position);
}

void ComponentData::setSize(Size size){
    this->rect.setSize(size);
}

bool ComponentData::operator==(const ComponentData& componentDataToCompare) const{
    if(this->id == componentDataToCompare.id && this->name == componentDataToCompare.name){
        return true;
    }
    return false;
}