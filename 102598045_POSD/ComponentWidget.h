#pragma once

#include "BaseWidget.h"
#include "Component.h"

class ComponentWidget : public BaseWidget{
public:
    ComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation);
    ~ComponentWidget();

    void updateWidget();
    Component* getComponent();
protected:
    Component* component;
    string getComponentID();
    void doPaint(QPainter* painter);
private:
    void drawSelectedFrame(QPainter* painter);
    string componentID;
};