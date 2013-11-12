#include "Point.h"

Point::Point(double coordinateX,double coordinateY) : coordinateX(coordinateX),coordinateY(coordinateY){}

double Point::getX(){
    return this->coordinateX;
}

double Point::getY(){
    return this->coordinateY;
}

bool Point::operator==(const Point& pointToCompare) const{
    if(this->coordinateX == pointToCompare.coordinateX && this->coordinateY == pointToCompare.coordinateY)
        return true;
    return false;
}

Point& Point::operator+=(const Point& pointToAdd){
    this->coordinateX += pointToAdd.coordinateX;
    this->coordinateY += pointToAdd.coordinateY;
    return *this;
}

Point Point::DefaultPoint(){
    return Point(0,0);
}