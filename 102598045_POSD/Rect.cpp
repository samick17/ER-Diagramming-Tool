#include "Rect.h"
#include "Number.h"

Rect::Rect(Point position,Size size) : position(position),size(size){
}

Point Rect::getPosition(){
    return this->position;
}

void Rect::setPosition(Point position){
    this->position = position;
}

void Rect::setCenterPosition(Point centerPosition){
    double halfWidth = this->size.getHalfWidth();
    double halfHeight = this->size.getHalfHeight();
    Point relativePosition = Point(centerPosition.getX()-halfWidth,centerPosition.getY()-halfHeight);
    this->position = relativePosition;
}

double Rect::getWidth(){
    return this->size.getWidth();
}

double Rect::getHeight(){
    return this->size.getHeight();
}

Size Rect::getSize(){
    return this->size;
}

void Rect::setSize(Size size){
    this->size = size;
}

double Rect::getLeft(){
    return this->position.getX();
}

double Rect::getRight(){
    return this->position.getX()+this->size.getWidth();
}

double Rect::getTop(){
    return this->position.getY();
}

double Rect::getBottom(){
    return this->position.getY()+this->size.getHeight();
}

double Rect::getCenterX(){
    return this->position.getX()+this->size.getWidth()/Number::Two;
}

double Rect::getCenterY(){
    return this->position.getY()+this->size.getHeight()/Number::Two;
}

Point Rect::getCenterPosition(){
    Point center = Point(this->getCenterX(),this->getCenterY());
    return center;
}

Point Rect::getCenterLeft(){
    Point centerLeft = Point(this->getLeft(),this->getCenterY());
    return centerLeft;
}

Point Rect::getCenterRight(){
    Point centerRight = Point(this->getRight(),this->getCenterY());
    return centerRight;
}

Point Rect::getCenterTop(){
    Point centerTop = Point(this->getCenterX(),this->getTop());
    return centerTop;
}

Point Rect::getCenterBottom(){
    Point centerBottom = Point(this->getCenterX(),this->getBottom());
    return centerBottom;
}

bool Rect::operator==(const Rect& rectToCompare) const{
    if(this->position == rectToCompare.position && this->size == rectToCompare.size)
        return true;
    return false;
}