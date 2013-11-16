#include "RectTest.h"

void RectTest::SetUp(){
    ASSERT_EQ(Point(),this->rect.getPosition());
    ASSERT_EQ(Size(),this->rect.getSize());
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
    this->rect.setPosition(point);
    ASSERT_EQ(point,this->rect.position);
}

TEST_F(RectTest,testSetCenterPosition){
    Point centerPosition = Point(324,115);
    this->rect.setCenterPosition(centerPosition);
    Point expectedPosition = Point(centerPosition.getX()-this->rect.size.getWidth()/2,centerPosition.getY()-this->rect.size.getHeight()/2);
    ASSERT_EQ(expectedPosition,this->rect.position);
}

TEST_F(RectTest,testGetWidth){
    ASSERT_EQ(Size().getWidth(),this->rect.getWidth());
    Size size = Size(321,450);
    this->rect = Rect(Point(),size);
    ASSERT_EQ(size.getWidth(),this->rect.getWidth());
}

TEST_F(RectTest,testGetHeight){
    ASSERT_EQ(Size().getHeight(),this->rect.getHeight());
    Size size = Size(321,450);
    this->rect = Rect(Point(),size);
    ASSERT_EQ(size.getHeight(),this->rect.getHeight());
}

TEST_F(RectTest,testSetSize){
    Size size = Size(30,120);
    this->rect.setSize(size);
    ASSERT_EQ(size,this->rect.size);
    size = Size(83,257);
    this->rect.setSize(size);
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
    ASSERT_EQ(this->rect.getPosition().getX()+this->rect.getWidth(),this->rect.getRight());
    this->rect = Rect(Point(),Size(644,287));
    ASSERT_EQ(this->rect.getPosition().getX()+this->rect.getWidth(),this->rect.getRight());
}

TEST_F(RectTest,testGetTop){
    ASSERT_EQ(this->rect.getPosition().getY(),this->rect.getTop());
    this->rect = Rect(Point(-24,-80),Size(728,824));
    ASSERT_EQ(this->rect.getPosition().getY(),this->rect.getTop());
}

TEST_F(RectTest,testGetBottom){
    ASSERT_EQ(this->rect.getPosition().getY()+this->rect.getHeight(),this->rect.getBottom());
    this->rect = Rect(Point(537,115),Size(1988,277));
    ASSERT_EQ(this->rect.getPosition().getY()+this->rect.getHeight(),this->rect.getBottom());
}

TEST_F(RectTest,testGetCenterX){
    ASSERT_EQ(this->rect.getPosition().getX()+this->rect.getWidth()/2,this->rect.getCenterX());
}

TEST_F(RectTest,testGetCenterY){
     ASSERT_EQ(this->rect.getPosition().getY()+this->rect.getHeight()/2,this->rect.getCenterY());
}

TEST_F(RectTest,testGetCenterPosition){
    Point point = this->rect.getPosition();
    Size size = this->rect.getSize();
    Point expectedPosition = Point(point.getX()+size.getHalfWidth(),point.getY()+size.getHalfHeight());
    ASSERT_EQ(expectedPosition,this->rect.getCenterPosition());
    point = Point(4684,241);
    size = Size(3258,211);
    this->rect = Rect(point,size);
    expectedPosition = Point(point.getX()+size.getHalfWidth(),point.getY()+size.getHalfHeight());
    ASSERT_EQ(expectedPosition,this->rect.getCenterPosition());
}

TEST_F(RectTest,testGetCenterLeft){
    Point centerLeft = Point(this->rect.getLeft(),this->rect.getCenterY());
    ASSERT_EQ(centerLeft,this->rect.getCenterLeft());
}

TEST_F(RectTest,testGetCenterRight){
    Point centerRight = Point(this->rect.getRight(),this->rect.getCenterY());
    ASSERT_EQ(centerRight,this->rect.getCenterRight());
}

TEST_F(RectTest,testGetCenterTop){
    Point centerTop = Point(this->rect.getCenterX(),this->rect.getTop());
    ASSERT_EQ(centerTop,this->rect.getCenterTop());
}

TEST_F(RectTest,testGetCenterBottom){
    Point centerBottom = Point(this->rect.getCenterX(),this->rect.getBottom());
    ASSERT_EQ(centerBottom,this->rect.getCenterBottom());
}

TEST_F(RectTest,testOperatorEquals){
    ASSERT_EQ(true,this->rect == Rect());
    ASSERT_EQ(true,this->rect == this->rect);
    this->rect = Rect(Point(0,1),Size());
    ASSERT_EQ(false,this->rect == Rect());
    ASSERT_EQ(true,this->rect == this->rect);
    this->rect = Rect(Point(),Size(49,50));
    ASSERT_EQ(false,this->rect == Rect());
    ASSERT_EQ(true,this->rect == this->rect);
}