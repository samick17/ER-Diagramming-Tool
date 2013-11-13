#pragma once

#include "Point.h"
#include "Size.h"

struct Rect{
public:
    Rect(Point position = Point(),Size size = Size());

    Point& getPosition();
    void setPosition(Point position);
    Size& getSize();
    void setSize(Size size);
    Point getCenterPosition();
    bool contains(Point point);

    bool operator==(const Rect& rectToCompare) const;
private:
    Point position;
    Size size;
};