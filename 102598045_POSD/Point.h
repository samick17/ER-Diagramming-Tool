#pragma once

struct Point{
public:
    Point(double coordinateX = 0,double coordinateY = 0);

    double getX();
    double getY();

    bool operator==(const Point& pointToOperate) const;
    Point& operator+=(const Point& pointToOperate);
    Point operator+(const Point& pointToOperate);
    Point operator-(const Point& pointToOperate);

    static Point DefaultPoint();
private:
    double coordinateX;
    double coordinateY;
};