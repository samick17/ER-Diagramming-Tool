#pragma once

#include "Point.h"
#include "Size.h"

struct Rect{
public:
    Rect(Point position,Size size);

    Point& getPosition();
    void setPosition(Point position);
    Size& getSize();
    void setSize(Size size);
    Point getCenterPosition();

    bool operator==(const Rect& rectToCompare) const;
private:
    Point position;
    Size size;
};