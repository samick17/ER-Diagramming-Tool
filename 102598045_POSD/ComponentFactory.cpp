#include "ComponentFactory.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringUtil.h"
#include "InvalidNodeTypeException.h"
#include "StringSymbol.h"

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
//return component pointer, if doesn't has such type, throw exception
Component* ComponentFactory::createComponent(string componentType){
	NewComponentFunction NewComponentFunctiontion = findNewComponentFunction(componentType);
	Component* component = NewComponentFunctiontion(ComponentData(StringUtil::intToString(count),StringSymbol::Empty));
	ComponentFactory::count++;
	return component;
}
//reset factory's ID
void ComponentFactory::resetFactory(){
	ComponentFactory::count = 0;
}
//return function pointer of new instance, if doesn't has such type, throw exception
NewComponentFunction ComponentFactory::findNewComponentFunction(string type){
	if(this->newComponentMap.containsKey(type)){
		return this->newComponentMap.get(type);
	}
	
	throw InvalidNodeTypeException();
}