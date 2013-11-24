#pragma once

#include "HashMap.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"
#include "Component.h"
#include "ComponentData.h"

class GraphicalPresentation;

typedef ComponentWidget* (*NewComponentWidgetFunction)(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    ComponentWidget* createComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
private:
    template<typename Type>
    static ComponentWidget* newComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);

    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
};

template<typename Type>
static ComponentWidget* WidgetFactory::newComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation){
    return new Type(componentData,graphicalPresentation);
}