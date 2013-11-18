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

BaseWidget* WidgetFactory::createComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation){
    string componentType = component->getType();
    NewComponentWidgetFunction newComponentWidgetFunctiontion = findNewComponentWidgetFunction(componentType);
    BaseWidget* componentWidget = newComponentWidgetFunctiontion(component,graphicalPresentation);
    return componentWidget;
}

NewComponentWidgetFunction WidgetFactory::findNewComponentWidgetFunction(string componentType){
    return this->newComponentWidgetMap.get(componentType);
}