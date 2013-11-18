#include "Rect.h"
#include "Number.h"

using namespace std;

const int Rect::CenterLeft = 0;
const int Rect::CenterRight = 1;
const int Rect::CenterTop = 2;
const int Rect::CenterBottom = 3;

Rect::Rect(Point position,Size size) : position(position),size(size){
    this->updateSpecialPoints();
}

Point Rect::getPosition(){
    return this->position;
}

void Rect::setPosition(Point position){
    this->position = position;
    this->updateSpecialPoints();
}

void Rect::setCenterPosition(Point centerPosition){
    double halfWidth = this->size.getHalfWidth();
    double halfHeight = this->size.getHalfHeight();
    Point relativePosition = Point(centerPosition.getX()-halfWidth,centerPosition.getY()-halfHeight);
    this->setPosition(relativePosition);
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
    this->updateSpecialPoints();
}

vector<Point> Rect::getSpecialPoints(){
    return this->specialPoints;
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
    return this->specialPoints[Rect::CenterLeft];
}

Point Rect::getCenterRight(){
    return this->specialPoints[Rect::CenterRight];
}

Point Rect::getCenterTop(){
    return this->specialPoints[Rect::CenterTop];
}

Point Rect::getCenterBottom(){
    return this->specialPoints[Rect::CenterBottom];
}

pair<Point,Point> Rect::getMinDistanceToRectPoint(Rect rect){
    double distance = DBL_MAX;
    pair<Point,Point> result;
    for each(Point candidatePoint in this->specialPoints)
        for each(Point comparedPoint in rect.getSpecialPoints()){
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

void Rect::updateSpecialPoints(){
    this->specialPoints.clear();
    this->specialPoints.push_back(Point(this->getLeft(),this->getCenterY()));
    this->specialPoints.push_back(Point(this->getRight(),this->getCenterY()));
    this->specialPoints.push_back(Point(this->getCenterX(),this->getTop()));
    this->specialPoints.push_back(Point(this->getCenterX(),this->getBottom()));
}