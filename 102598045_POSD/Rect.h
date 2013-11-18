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
public:
    Rect(Point position = Point(),Size size = Size());

    Point getPosition();
    void setPosition(Point position);
    void setCenterPosition(Point centerPosition);
    double getWidth();
    double getHeight();
    Size getSize();
    void setSize(Size size);

    vector<Point> getSpecialPoints();
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
    pair<Point,Point> getMinDistanceToRectPoint(Rect rect);

    bool operator==(const Rect& rectToCompare) const;
private:
    static const int CenterLeft,CenterRight,CenterTop,CenterBottom;
    void updateSpecialPoints();
    vector<Point> specialPoints;
    Point position;
    Size size;
};