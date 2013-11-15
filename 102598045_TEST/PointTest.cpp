#include "PointTest.h"

void PointTest::SetUp(){
    ASSERT_EQ(0,point.coordinateX);
    ASSERT_EQ(0,point.coordinateY);
}

void PointTest::TearDown(){
}