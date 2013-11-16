#include "RectTest.h"

void RectTest::SetUp(){
}

void RectTest::TearDown(){
}

TEST_F(RectTest,testGetPosition){
    //Test Default Position
    ASSERT_EQ(Point(),this->rect.getPosition());
    Point point = Point(0,0);
    point = Point(123,45);
    //Test Construct Position
    this->rect = Rect(point);
    ASSERT_EQ(point,this->rect.getPosition());
}

TEST_F(RectTest,testSetPosition){
    Point point = Point(44,800);
    this->rect.setPosition(point);
    ASSERT_EQ(point,this->rect.position);
    point = Point(-105,-35);
    ASSERT_EQ(point,this->rect.position);
}

TEST_F(RectTest,testGetSize){
    ASSERT_EQ(Size(),this->rect.getSize());
    Size size = Size(321,450);
    this->rect = Rect(Point(),size);
    ASSERT_EQ(size,this->rect.getSize());
}

TEST_F(RectTest,testSetSize){
    Size size = Size(30,120);
    this->rect.setSize(size);
    ASSERT_EQ(size,this->rect.size);
    size = Size(83,257);
    ASSERT_EQ(size,this->rect.size);
}

TEST_F(RectTest,testGetLeft){
    ASSERT_EQ(this->rect.getPosition().getX(),this->rect.getLeft());
    Point point = Point(384,217);
    this->rect = Rect(point);
    ASSERT_EQ(point.getX(),this->rect.getLeft());
    ASSERT_EQ(this->rect.getPosition().getX(),this->rect.getLeft());
}

TEST_F(RectTest,testGetRight){
    ASSERT_EQ(this->rect.getPosition().getX()+this->rect.getSize().getWidth(),this->rect.getRight());
    this->rect = Rect(Point(),Size(644,287));
    ASSERT_EQ(this->rect.getPosition().getX()+this->rect.getSize().getWidth(),this->rect.getRight());
}

TEST_F(RectTest,testGetTop){
    ASSERT_EQ(this->rect.getPosition().getY(),this->rect.getTop());
    this->rect = Rect(Point(-24,-80),Size(728,824));
    ASSERT_EQ(this->rect.getPosition().getY(),this->rect.getTop());
}

TEST_F(RectTest,testGetBottom){
    ASSERT_EQ(this->rect.getPosition().getY()+this->rect.getSize().getHeight(),this->rect.getBottom());
    this->rect = Rect(Point(537,115),Size(1988,277));
    ASSERT_EQ(this->rect.getPosition().getY()+this->rect.getSize().getHeight(),this->rect.getBottom());
}

TEST_F(RectTest,testGetCenterX){
    ASSERT_EQ(this->rect.getPosition()+this->rect.getSize().getWidth()/2,this->rect.getCenterX());
}

TEST_F(RectTest,testGetCenterY){}

TEST_F(RectTest,testGetCenterPosition){}

TEST_F(RectTest,testGetCenterLeft){}

TEST_F(RectTest,testGetCenterRight){}

TEST_F(RectTest,testGetCenterTop){}

TEST_F(RectTest,testGetCenterBottom){}

TEST_F(RectTest,testOperatorEquals){
}