#pragma once

#include "HashMap.h"
#include "ComponentWidget.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"

class GraphicalPresentation;

typedef ComponentWidget* (*NewComponentWidgetFunction)(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    ComponentWidget* createComponentWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);
private:
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    template<typename Type>
    static ComponentWidget* newComponentWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation);
};

template<typename Type>
static ComponentWidget* WidgetFactory::newComponentWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation){
    return new Type(componentWidgetData,graphicalPresentation);
}