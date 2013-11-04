#include "ComponentWidgetData.h"

ComponentWidgetData::ComponentWidgetData(string text,int positionX,int positionY,bool isUnderLined) : text(text),positionX(positionX),positionY(positionY),isUnderLined(isUnderLined){
}

ComponentWidgetData::~ComponentWidgetData(){
}

string ComponentWidgetData::getText(){
    return this->text;
}

void ComponentWidgetData::setText(string text){
	this->text = text;
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