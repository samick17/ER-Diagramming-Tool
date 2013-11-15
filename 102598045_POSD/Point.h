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

    bool operator==(const Point& pointToOperate) const;
    Point& operator+=(const Point& pointToOperate);
    Point operator+(const Point& pointToOperate);
    Point operator-(const Point& pointToOperate);

    static Point DefaultPoint();
private:
    double coordinateX;
    double coordinateY;
};