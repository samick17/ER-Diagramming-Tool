#include "ConnectorData.h"
#include "ComponentType.h"

ConnectorData::ConnectorData(string id,string name,Point sourcePoint,Point targetPoint) : ComponentData(ComponentType::TypeConnector,id,name){
    this->setPointPair(pair<Point,Point>(sourcePoint,targetPoint));
}

ConnectorData::~ConnectorData(){
}

Point ConnectorData::getSourcePoint(){
    return this->sourcePoint;
}

void ConnectorData::setSourcePoint(Point sourcePoint){
    this->sourcePoint = sourcePoint;
}

Point ConnectorData::getTargetPoint(){
    return this->targetPoint;
}

void ConnectorData::setTargetPoint(Point targetPoint){
    this->targetPoint = targetPoint;
}

void ConnectorData::setPointPair(pair<Point,Point> pointPair){
    this->sourcePoint = pointPair.first;
    this->targetPoint = pointPair.second;
    //set Position
    double left = min(sourcePoint.getX(),targetPoint.getX());
    double top = min(sourcePoint.getY(),targetPoint.getY());
    Point position = Point(left,top);
    this->setPosition(position);
    //set Size
    double width = abs(sourcePoint.getX()-targetPoint.getX());
    double height = abs(sourcePoint.getY()-targetPoint.getY());
    Size size = Size(width,height);
    this->setSize(size);
}