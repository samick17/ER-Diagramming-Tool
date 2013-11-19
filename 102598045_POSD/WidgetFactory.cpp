#include "WidgetFactory.h"
#include "ComponentType.h"
#include "GraphicalPresentation.h"

WidgetFactory::WidgetFactory(){
    this->newComponentWidgetMap.put(ComponentType::TypeAttribute,newComponentWidget<AttributeWidget>);
    this->newComponentWidgetMap.put(ComponentType::TypeEntity,newComponentWidget<EntityWidget>);
    this->newComponentWidgetMap.put(ComponentType::TypeRelationShip,newComponentWidget<RelationShipWidget>);
    this->newComponentWidgetMap.put(ComponentType::TypeConnector,newComponentWidget<ConnectorWidget>);
}

WidgetFactory::~WidgetFactory(){
}

ComponentWidget* WidgetFactory::createComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation){
    string componentType = componentData->getType();
    NewComponentWidgetFunction newComponentWidgetFunctiontion = findNewComponentWidgetFunction(componentType);
    ComponentWidget* componentWidget = newComponentWidgetFunctiontion(componentData,graphicalPresentation);
    return componentWidget;
}

NewComponentWidgetFunction WidgetFactory::findNewComponentWidgetFunction(string componentType){
    return this->newComponentWidgetMap.get(componentType);
}