#pragma once

#include <string>
#include "Component.h"

using namespace std;

struct ComponentWidgetData{
public:
    ComponentWidgetData(Component* component,int positionX,int positionY,bool isUnderLined = false);
    ~ComponentWidgetData();

    Component* getComponent();
    int getPositionX();
    void setPositionX(int positionX);
    int getPositionY();
    void setPositionY(int positionY);
    bool getIsUnderLined();
    void setIsUnderLined(bool isUnderLined);
private:
    Component* component;
    int positionX;
    int positionY;
    bool isUnderLined;
};