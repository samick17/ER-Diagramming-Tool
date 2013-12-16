#include "Point.h"
#include <math.h>

const Point Point::Zero = Point();

Point::Point(double coordinateX,double coordinateY) : coordinateX(coordinateX),coordinateY(coordinateY){
}

double Point::getX(){
    return this->coordinateX;
}

double Point::getY(){
    return this->coordinateY;
}

double Point::getDistance(Point point){
    double deltaX = point.getX()-this->getX();
    double deltaY = point.getY()-this->getY();
    double distance = sqrt(deltaX*deltaX+deltaY*deltaY);
    return distance;
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