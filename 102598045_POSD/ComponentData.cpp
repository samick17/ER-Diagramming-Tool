#include "ComponentData.h"
#include "Number.h"

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