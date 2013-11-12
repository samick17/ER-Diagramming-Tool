#include "ComponentWidgetData.h"

ComponentWidgetData::ComponentWidgetData(Component* component,int positionX,int positionY,bool isUnderLined) : component(component),positionX(positionX),positionY(positionY),isUnderLined(isUnderLined){
}

ComponentWidgetData::~ComponentWidgetData(){
}

Component* ComponentWidgetData::getComponent(){
    return this->component;
}

int ComponentWidgetData::getPositionX(){
    return this->positionX;
}

void ComponentWidgetData::setPositionX(int positionX){
    this->positionX = positionX;
}

int ComponentWidgetData::getPositionY(){
    return this->positionY;
}

void ComponentWidgetData::setPositionY(int positionY){
    this->positionY = positionY;
}

bool ComponentWidgetData::getIsUnderLined(){
    return this->isUnderLined;
}

void ComponentWidgetData::setIsUnderLined(bool isUnderLined){
    this->isUnderLined = isUnderLined;
}