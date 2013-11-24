#pragma once

#include "Point.h"
#include "Size.h"
#include <utility>
#include <vector>

using namespace std;

struct Rect{
    friend class RectTest;
    FRIEND_TEST(RectTest,testSetPosition);
    FRIEND_TEST(RectTest,testSetCenterPosition);
    FRIEND_TEST(RectTest,testSetSize);
    FRIEND_TEST(RectTest,testUpdateControlPoints);
public:
    Rect(Point position = Point(),Size size = Size());

    Point getPosition();
    void setPosition(Point position);
    void setCenterPosition(Point centerPosition);
    double getWidth();
    double getHeight();
    Size getSize();
    void setSize(Size size);

    vector<Point> getControlPoints();
    double getLeft();
    double getRight();
    double getTop();
    double getBottom();
    double getCenterX();
    double getCenterY();

    Point getCenterPosition();
    Point getCenterLeft();
    Point getCenterRight();
    Point getCenterTop();
    Point getCenterBottom();
    pair<Point,Point> getMinDistanceToRectPoint(const Rect& rect);

    bool operator==(const Rect& rectToCompare) const;
private:
    void updateControlPoints();
    static const int CenterLeft,CenterRight,CenterTop,CenterBottom;
    vector<Point> controlPoints;
    Point position;
    Size size;
};