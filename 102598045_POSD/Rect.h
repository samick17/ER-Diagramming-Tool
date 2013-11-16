#pragma once

#include "Point.h"
#include "Size.h"

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
    
    bool operator==(const Rect& rectToCompare) const;
private:
    Point position;
    Size size;
};