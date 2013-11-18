#pragma once

#include "HashMap.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"
#include "Component.h"
#include "ComponentData.h"

class GraphicalPresentation;

typedef BaseWidget* (*NewComponentWidgetFunction)(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    BaseWidget* createComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
private:
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    template<typename Type>
    static BaseWidget* newComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
};

template<typename Type>
static BaseWidget* WidgetFactory::newComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation){
    return new Type(componentData,graphicalPresentation);
}