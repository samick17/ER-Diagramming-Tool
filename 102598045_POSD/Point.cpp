#include "Point.h"

Point::Point(double coordinateX,double coordinateY) : coordinateX(coordinateX),coordinateY(coordinateY){}

double Point::getX(){
    return this->coordinateX;
}

double Point::getY(){
    return this->coordinateY;
}

bool Point::operator==(const Point& pointToOperate) const{
    if(this->coordinateX == pointToOperate.coordinateX && this->coordinateY == pointToOperate.coordinateY)
        return true;
    return false;
}

Point& Point::operator+=(const Point& pointToOperate){
    this->coordinateX += pointToOperate.coordinateX;
    this->coordinateY += pointToOperate.coordinateY;
    return *this;
}

Point Point::operator+(const Point& pointToOperate){
    Point point = *this;
    point.coordinateX += pointToOperate.coordinateX;
    point.coordinateY += pointToOperate.coordinateY;
    return point;
}


Point Point::operator-(const Point& pointToOperate){
    Point point = *this;
    point.coordinateX -= pointToOperate.coordinateX;
    point.coordinateY -= pointToOperate.coordinateY;
    return point;
}