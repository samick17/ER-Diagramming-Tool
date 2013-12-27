#include "ComponentFactory.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringUtil.h"
#include "InvalidNodeTypeException.h"

using namespace std;

ComponentFactory::ComponentFactory(){
    this->newComponentMap.put(ComponentType::TypeAttribute,newComponent<Attribute>);
    this->newComponentMap.put(ComponentType::TypeEntity,newComponent<Entity>);
    this->newComponentMap.put(ComponentType::TypeRelationShip,newComponent<RelationShip>);
    this->newComponentMap.put(ComponentType::TypeConnector,newComponent<Connector>);
}

ComponentFactory::~ComponentFactory(){
}
//return component pointer, if doesn't has such type, throw exception
Component* ComponentFactory::createComponent(string componentType,string componentID,string name){
    NewComponentFunction newComponentFunctiontion = findNewComponentFunction(componentType);
    Component* component = newComponentFunctiontion(componentID,name);
    return component;
}
//return function pointer of new instance, if doesn't has such type, throw exception
NewComponentFunction ComponentFactory::findNewComponentFunction(string type){
    if(this->newComponentMap.containsKey(type))
        return this->newComponentMap.get(type);
    throw InvalidNodeTypeException();
}