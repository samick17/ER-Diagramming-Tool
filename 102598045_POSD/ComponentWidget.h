#pragma once

#include "BaseWidget.h"
#include "ComponentData.h"

class ComponentWidget : public BaseWidget{
public:
    ComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation);
    ~ComponentWidget();

    void updateWidget();
    ComponentData* getComponentData();
protected:
    ComponentData* componentData;
    string getComponentID();
    void doPaint(QPainter* painter);
private:
    void drawSelectedFrame(QPainter* painter);
    string componentID;
};