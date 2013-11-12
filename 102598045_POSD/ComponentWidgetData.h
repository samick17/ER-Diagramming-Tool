#pragma once

#include <string>
#include "Component.h"
#include "Rect.h"

using namespace std;

struct ComponentWidgetData{
public:
    ComponentWidgetData(Component* component,Rect rect,bool isUnderLined = false);
    ~ComponentWidgetData();

    Component* getComponent();
    Rect& getRect();
    void setPosition(Point position);
    void setSize(Size size);
    bool getIsUnderLined();
    void setIsUnderLined(bool isUnderLined);
private:
    Component* component;
    Rect rect;
    bool isUnderLined;
};