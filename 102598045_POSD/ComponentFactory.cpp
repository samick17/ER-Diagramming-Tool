#include "ComponentFactory.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringUtil.h"
#include "InvalidNodeTypeException.h"
#include "StringSymbol.h"
#include "WidgetDefaultSetting.h"
#include <iostream>

using namespace std;

int ComponentFactory::count = 0;
int ComponentFactory::attributeCount = 0;
int ComponentFactory::entityCount = 0;
int ComponentFactory::relationShipCount = 0;
int ComponentFactory::connectorCount = 0;

ComponentFactory::ComponentFactory(){
    this->newComponentMap.put(ComponentType::TypeAttribute,newComponent<Attribute>);
    this->newComponentMap.put(ComponentType::TypeEntity,newComponent<Entity>);
    this->newComponentMap.put(ComponentType::TypeRelationShip,newComponent<RelationShip>);
    this->newComponentMap.put(ComponentType::TypeConnector,newComponent<Connector>);
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeAttribute,WidgetDefaultSetting::AttributeOffsetX));
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeEntity,WidgetDefaultSetting::EntityOffsetX));
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeRelationShip,WidgetDefaultSetting::RelationShipOffsetX));
    this->componentTypeMapOffsetX.insert(pair<string,double>(ComponentType::TypeConnector,0));
    this->componentTypeCountMap.put(ComponentType::TypeAttribute,&ComponentFactory::attributeCount);
    this->componentTypeCountMap.put(ComponentType::TypeEntity,&ComponentFactory::entityCount);
    this->componentTypeCountMap.put(ComponentType::TypeRelationShip,&ComponentFactory::relationShipCount);
    this->componentTypeCountMap.put(ComponentType::TypeConnector,&ComponentFactory::connectorCount);
}

ComponentFactory::~ComponentFactory(){
}
//return component pointer, if doesn't has such type, throw exception
Component* ComponentFactory::createComponent(string componentType,string name){
    NewComponentFunction newComponentFunctiontion = findNewComponentFunction(componentType);
    Component* component = newComponentFunctiontion(StringUtil::intToString(count),name);
    ComponentFactory::count++;
    auto countIterator = this->componentTypeCountMap.get(componentType);
    component->setPosition(Point(componentTypeMapOffsetX.find(componentType)->second,WidgetDefaultSetting::WidgetStartY+(*countIterator)*WidgetDefaultSetting::WidgetOffsetY));
    (*countIterator)++;
    return component;
}
//reset factory's ID
void ComponentFactory::resetFactory(){
    ComponentFactory::count = 0;
    ComponentFactory::attributeCount = 0;
    ComponentFactory::entityCount = 0;
    ComponentFactory::relationShipCount = 0;
    ComponentFactory::connectorCount = 0;
}
//return function pointer of new instance, if doesn't has such type, throw exception
NewComponentFunction ComponentFactory::findNewComponentFunction(string type){
    if(this->newComponentMap.containsKey(type))
        return this->newComponentMap.get(type);
    throw InvalidNodeTypeException();
}