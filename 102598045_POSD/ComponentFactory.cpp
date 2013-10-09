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
	this->newComponentMap.insert(NewComponentFuncPair(ComponentType::TypeConnector,newComponent<Connector>));
	this->newComponentMap.insert(NewComponentFuncPair(ComponentType::TypeAttribute,newComponent<Attribute>));
	this->newComponentMap.insert(NewComponentFuncPair(ComponentType::TypeEntity,newComponent<Entity>));
	this->newComponentMap.insert(NewComponentFuncPair(ComponentType::TypeRelationShip,newComponent<RelationShip>));
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
	hash_map<string,NewComponentFunc>::iterator noewCompFuncIterator;
	if((noewCompFuncIterator = newComponentMap.find(type)) != newComponentMap.end())	
		return noewCompFuncIterator->second;
	
	throw InvalidNodeTypeException();
}