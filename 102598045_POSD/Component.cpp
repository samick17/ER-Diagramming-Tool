#include "Component.h"
#include "StringUtil.h"
#include "CharSymbol.h"

Component::Component(){
}

Component::~Component(){
    delete this->componentData;
}

string Component::getID(){
    return this->componentData->getID();
}

void Component::setID(string id){
    return this->componentData->setID(id);
}

string Component::getType(){
    return this->componentData->getType();
}

string Component::getClassName(){
    return this->componentData->getClassName();
}

string Component::getName(){
    return this->componentData->getName();
}

void Component::setName(string name){
    this->componentData->setName(name);
}

Rect Component::getRect(){
    return this->componentData->getRect();
}

void Component::setCenterPosition(Point position){
    this->componentData->setCenterPosition(position);
}

void Component::setSize(Size size){
    this->componentData->setSize(size);
}

ComponentData* Component::getComponentData(){
    return this->componentData;
}

HashMap<string,Component*> Component::getAllConnections(){
    return this->connectionMap;
}

//if no such connection in set, connect to target
void Component::connectTo(Component* target){
    if(!this->connectionMap.containsKey(target->getID()))
        this->connectionMap.put(target->getID(),target);
}

//if has such connection in set, disconnect to target
void Component::disconnectTo(Component* target){
    if(this->connectionMap.containsKey(target->getID()))
        this->connectionMap.remove(target->getID());
}

bool Component::hasSizeToConnect(){
    return true;
}

//make sure two node has been connected
bool Component::hasConnectedTo(Component* target){
    if(this == target)
        return false;
    for each(Component* component in this->connectionMap){
        HashMap<string,Component*> compConnMap = component->connectionMap;
        if(compConnMap.containsKey(target->getID()))
            return true;
    }
    return false;
}