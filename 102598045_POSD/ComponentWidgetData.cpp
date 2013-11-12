#include "ComponentWidgetData.h"

ComponentWidgetData::ComponentWidgetData(Component* component,Rect rect,bool isUnderLined) : component(component),rect(rect),isUnderLined(isUnderLined){
}

ComponentWidgetData::~ComponentWidgetData(){
}

Component* ComponentWidgetData::getComponent(){
    return this->component;
}

Rect& ComponentWidgetData::getRect(){
    return this->rect;
}

void ComponentWidgetData::setPosition(Point position){
    this->rect.setPosition(position);
}

void ComponentWidgetData::setSize(Size size){
    this->rect.setSize(size);
}

bool ComponentWidgetData::getIsUnderLined(){
    return this->isUnderLined;
}

void ComponentWidgetData::setIsUnderLined(bool isUnderLined){
    this->isUnderLined = isUnderLined;
}