#pragma once

#include "Component.h"
#include "Presentation.h"
#include "WidgetFactory.h"

class GraphicalUI;

class GraphicalPresentation{
public:
    GraphicalPresentation(Presentation* presentation);
    ~GraphicalPresentation();

    HashMap<string,ComponentWidget*> getAllComponentWidgets();

    void openFile();
    void saveFile();
    void close();
private:
    Presentation* presentation;
    GraphicalUI* graphicalUI;
    HashMap<string,ComponentWidget*> componentWidgetMap;
    void deleteAndClearAllComponentWidget();
    void updateComponentWidgetMap();
};