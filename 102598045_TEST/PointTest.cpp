#include "PointTest.h"

void PointTest::SetUp(){
    ASSERT_EQ(0,point.coordinateX);
    ASSERT_EQ(0,point.coordinateY);
}

void PointTest::TearDown(){
}
//Test operator==
TEST_F(PointTest,testOperatorEquals){
    ASSERT_EQ(true,this->point == Point());
    ASSERT_EQ(false,this->point == Point(0,1));
    ASSERT_EQ(false,this->point == Point(1,0));
    ASSERT_EQ(false,this->point == Point(1,1));

    Point expected = Point(37,254);
    ASSERT_EQ(false,this->point == expected);

    this->point = expected;
    ASSERT_EQ(true,this->point == expected);
}
//Test operator+=
TEST_F(PointTest,testPlusEquals){
    this->point += Point();
    ASSERT_EQ(Point(),this->point);
    Point point = Point(287,2448);
    this->point += point;
    ASSERT_EQ(point,this->point);

    this->point = point;
    point = Point(-30,-358);
    double expectedX = this->point.getX()+point.getX();
    double expectedY = this->point.getY()+point.getY();
    this->point += point;
    Point expected = Point(expectedX,expectedY);
    ASSERT_EQ(expectedX,this->point.getX());
    ASSERT_EQ(expectedY,this->point.getY());
    ASSERT_EQ(expected,this->point);
}
//Test operator+
TEST_F(PointTest,testPlus){
    Point pointToOperate = Point(87,-244);
    ASSERT_EQ(pointToOperate,this->point + pointToOperate);
    ASSERT_EQ(Point(),this->point);
    pointToOperate = Point();
    ASSERT_EQ(this->point,this->point + pointToOperate);
}
//Test operator-
TEST_F(PointTest,testMinus){
    Point pointToOperate = Point(-578,-416);
    ASSERT_EQ(Point(578,416),this->point - pointToOperate);
    ASSERT_EQ(Point(),this->point);
}