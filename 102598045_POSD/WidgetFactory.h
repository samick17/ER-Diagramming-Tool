#pragma once

#include "HashMap.h"
#include "ComponentWidget.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"

typedef ComponentWidget* (*NewComponentWidgetFunction)();

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    ComponentWidget* createComponentWidget(string componentType);
private:
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    template<typename Type>
    static ComponentWidget* newComponentWidget();
};

template<typename Type>
static ComponentWidget* WidgetFactory::newComponentWidget(){
    return new Type();
}