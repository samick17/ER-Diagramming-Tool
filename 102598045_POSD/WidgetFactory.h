#pragma once

#include "HashMap.h"
#include "ComponentWidget.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"

class GraphicalPresentation;

typedef ComponentWidget* (*NewComponentWidgetFunction)(Component* component,GraphicalPresentation* graphicalPresentation);

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    ComponentWidget* createComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
private:
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    template<typename Type>
    static ComponentWidget* newComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
};

template<typename Type>
static ComponentWidget* WidgetFactory::newComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation){
    return new Type(component,graphicalPresentation);
}