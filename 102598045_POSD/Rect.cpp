#include "Rect.h"
#include "Number.h"

Rect::Rect(Point position,Size size) : position(position),size(size){
}

Point& Rect::getPosition(){
    return this->position;
}

void Rect::setPosition(Point position){
    this->position = position;
}

Size& Rect::getSize(){
    return this->size;
}

void Rect::setSize(Size size){
    this->size = size;
}

Point Rect::getCenterPosition(){
    double centerX = this->position.getX()+this->size.getWidth()/Number::Two;
    double centerY = this->position.getY()+this->size.getHeight()/Number::Two;
    Point center = Point(centerX,centerY);
    return center;
}

bool Rect::contains(Point point){
	Point position = this->getPosition();
	Size size = this->getSize();
	if(point.getX()<position.getX())
		return false;
	if(point.getY()<position.getY())
		return false;
	if(point.getX()>position.getX()+size.getWidth())
		return false;
	if(point.getY()>position.getY()+size.getHeight())
		return false;
    return true;
}

bool Rect::operator==(const Rect& rectToCompare) const{
    if(this->position == rectToCompare.position && this->size == rectToCompare.size)
        return true;
    return false;
}