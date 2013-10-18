#include "ComponentFactory.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringUtil.h"
#include "InvalidNodeTypeException.h"

using namespace std;

int ComponentFactory::count = 0;

ComponentFactory::ComponentFactory(){	
	this->newComponentMap.put(ComponentType::TypeConnector,newComponent<Connector>);
	this->newComponentMap.put(ComponentType::TypeAttribute,newComponent<Attribute>);
	this->newComponentMap.put(ComponentType::TypeEntity,newComponent<Entity>);
	this->newComponentMap.put(ComponentType::TypeRelationShip,newComponent<RelationShip>);
}

ComponentFactory::~ComponentFactory(){
}
//@return component pointer, if doesn't has such type, throw exception
Component* ComponentFactory::createComponent(string componentType){
	NewComponentFunc newComponentFunction = findNewComponentFunction(componentType);
	Component* component = newComponentFunction(ComponentData(StringUtil::intToString(count),""));
	ComponentFactory::count++;
	return component;
}
//reset factory's ID
void ComponentFactory::resetFactory(){
	ComponentFactory::count = 0;
}
//@return function pointer of new instance, if doesn't has such type, throw exception
NewComponentFunc ComponentFactory::findNewComponentFunction(string type){
	if(this->newComponentMap.containsKey(type)){
		return this->newComponentMap.get(type);
	}
	
	throw InvalidNodeTypeException();
}