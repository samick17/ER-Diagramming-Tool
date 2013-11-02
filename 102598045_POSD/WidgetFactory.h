#pragma once

#include "HashMap.h"
#include "ComponentWidget.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"

class GraphicalPresentation;

typedef ComponentWidget* (*NewComponentWidgetFunction)(GraphicalPresentation* graphicalPresentation);

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    ComponentWidget* createComponentWidget(string componentType,GraphicalPresentation* graphicalPresentation);
private:
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    template<typename Type>
    static ComponentWidget* newComponentWidget(GraphicalPresentation* graphicalPresentation);
};

template<typename Type>
static ComponentWidget* WidgetFactory::newComponentWidget(GraphicalPresentation* graphicalPresentation){
    return new Type(graphicalPresentation);
}