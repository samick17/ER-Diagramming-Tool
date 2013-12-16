#pragma once

#include <gtest/gtest_prod.h> 

struct Point{
    friend class PointTest;
    FRIEND_TEST(PointTest,testOperatorEquals);
    FRIEND_TEST(PointTest,testOperatorPlusEquals);
    FRIEND_TEST(PointTest,testOperatorPlus);
    FRIEND_TEST(PointTest,testOperatorMinus);
public:
    Point(double coordinateX = 0,double coordinateY = 0);

    double getX();
    double getY();
    double getDistance(Point point);

    bool operator==(const Point& pointToOperate) const;
    Point& operator+=(const Point& pointToOperate);
    Point operator+(const Point& pointToOperate);
    Point operator-(const Point& pointToOperate);

    const static Point Zero;
private:
    double coordinateX;
    double coordinateY;
};