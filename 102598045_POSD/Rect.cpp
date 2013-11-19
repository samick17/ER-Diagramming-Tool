#include "Rect.h"
#include "Number.h"

using namespace std;

const int Rect::CenterLeft = 0;
const int Rect::CenterRight = 1;
const int Rect::CenterTop = 2;
const int Rect::CenterBottom = 3;

Rect::Rect(Point position,Size size) : position(position),size(size){
    this->updateControlPoints();
}

Point Rect::getPosition(){
    return this->position;
}

void Rect::setPosition(Point position){
    this->position = position;
    this->updateControlPoints();
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
    this->updateControlPoints();
}

vector<Point> Rect::getControlPoints(){
    return this->controlPoints;
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
    return this->controlPoints[Rect::CenterLeft];
}

Point Rect::getCenterRight(){
    return this->controlPoints[Rect::CenterRight];
}

Point Rect::getCenterTop(){
    return this->controlPoints[Rect::CenterTop];
}

Point Rect::getCenterBottom(){
    return this->controlPoints[Rect::CenterBottom];
}
//calculate this & rect's minmun distance Point
pair<Point,Point> Rect::getMinDistanceToRectPoint(const Rect& rect){
    double distance = DBL_MAX;
    pair<Point,Point> result;
    for each(Point candidatePoint in this->controlPoints)
        for each(Point comparedPoint in rect.controlPoints){
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

void Rect::updateControlPoints(){
    this->controlPoints.clear();
    this->controlPoints.push_back(Point(this->getLeft(),this->getCenterY()));
    this->controlPoints.push_back(Point(this->getRight(),this->getCenterY()));
    this->controlPoints.push_back(Point(this->getCenterX(),this->getTop()));
    this->controlPoints.push_back(Point(this->getCenterX(),this->getBottom()));
}