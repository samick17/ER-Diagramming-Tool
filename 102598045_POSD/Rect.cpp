#include "Rect.h"
#include "Number.h"
#include <vector>

using namespace std;

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

pair<Point,Point> Rect::getMinDistanceToRectPoint(Rect rect){
    vector<Point> candidatePointVector;
    candidatePointVector.push_back(this->getCenterLeft());
    candidatePointVector.push_back(this->getCenterRight());
    candidatePointVector.push_back(this->getCenterTop());
    candidatePointVector.push_back(this->getCenterBottom());
    vector<Point> comparedPointVector;
    comparedPointVector.push_back(rect.getCenterLeft());
    comparedPointVector.push_back(rect.getCenterRight());
    comparedPointVector.push_back(rect.getCenterTop());
    comparedPointVector.push_back(rect.getCenterBottom());
    double distance = DBL_MAX;
    pair<Point,Point> result;
    for each(Point candidatePoint in candidatePointVector)
        for each(Point comparedPoint in comparedPointVector){
        double distanceBuffer = candidatePoint.getDistance(comparedPoint);
            if(distanceBuffer<distance){
                result = pair<Point,Point>(candidatePoint,comparedPoint);
                distance = distanceBuffer;
            }
        }
    return result;
}

bool Rect::operator==(const Rect& rectToCompare) const{
    if(this->position == rectToCompare.position && this->size == rectToCompare.size)
        return true;
    return false;
}