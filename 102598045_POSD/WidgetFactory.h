#pragma once

#include "HashMap.h"
#include "AttributeWidget.h"
#include "EntityWidget.h"
#include "RelationShipWidget.h"
#include "ConnectorWidget.h"

class GraphicalPresentation;

typedef BaseWidget* (*NewComponentWidgetFunction)(Component* component,GraphicalPresentation* graphicalPresentation);

class WidgetFactory{
public:
    WidgetFactory();
    ~WidgetFactory();

    BaseWidget* createComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    BaseWidget* createPreviewWidget(GraphicalPresentation* graphicalPresentation);
private:
    HashMap<string,NewComponentWidgetFunction> newComponentWidgetMap;
    NewComponentWidgetFunction findNewComponentWidgetFunction(string componentType);
    template<typename Type>
    static BaseWidget* newComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
};

template<typename Type>
static BaseWidget* WidgetFactory::newComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation){
    return new Type(component,graphicalPresentation);
}