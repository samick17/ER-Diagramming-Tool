#include "Component.h"
#include "StringUtil.h"
#include "ComponentType.h"

Component::Component(ComponentData componentData) : componentData(componentData){
}

Component::~Component(){
}

string Component::toString(){
	string name = this->getName();
	string result = this->getType()+(name==""?"":", " +name);
	return result;
}

string Component::getID(){
	return this->componentData.getID();
}

void Component::setID(string id){
	this->componentData.setID(id);
}

string Component::getType(){
	return ComponentType::TypeComponent;
}

string Component::getName(){
	return this->componentData.getName();
}

void Component::setName(string name){
	this->componentData.setName(name);
}

string Component::getClassName(){
	return StringUtil::split(typeid(*this).name(),' ')[1];
}
//if no such connection in set, connect to target
void Component::connectTo(Component* target){		
	if(this->connectionSet.find(target) == this->connectionSet.end())
		this->connectionSet.insert(target);
}
//if has such connection in set, disconnect to target
void Component::disconnectTo(Component* target){	
	if(this->connectionSet.find(target) != this->connectionSet.end())	
		this->connectionSet.erase(target);	
}

bool Component::hasSizeToConnect(){
	return true;
}

//make sure two node has been connected
bool Component::hasConnectedTo(Component* target){
	if(this == target)
		return false;
	for each(Component* component in this->connectionSet){
		set<Component*> compConnSet = component->connectionSet;
		if (compConnSet.find(target) != compConnSet.end()) 		
			return true;		
	}	
	return false;
}

set<Component*> Component::getAllConnectors(){
	return this->connectionSet;
}