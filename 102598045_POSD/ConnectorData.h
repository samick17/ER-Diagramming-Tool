#pragma once

#include "ComponentData.h"

struct ConnectorData : public ComponentData{
public:
    ConnectorData(string id,string name = StringSymbol::Empty,Point sourcePoint = Point(),Point targetPoint = Point());
    ~ConnectorData();

    Point getSourcePoint();
    void setSourcePoint(Point sourcePoint);
    Point getTargetPoint();
    void setTargetPoint(Point targetPoint);
    void setPointPair(pair<Point,Point> pointPair);
private:
    Point sourcePoint,targetPoint;
};