#include "SizeTest.h"

void SizeTest::SetUp(){
}

void SizeTest::TearDown(){
}

TEST_F(SizeTest,testGetHalfWidth){
    ASSERT_EQ(this->size.getWidth()/2,this->size.getHalfWidth());
    this->size = Size(380,470);
    ASSERT_EQ(190,this->size.getHalfWidth());
}

TEST_F(SizeTest,testGetHalfHeight){
    ASSERT_EQ(this->size.getHeight()/2,this->size.getHalfHeight());
    this->size = Size(600,910);
    ASSERT_EQ(455,this->size.getHalfHeight());
}

TEST_F(SizeTest,testOperatorEquals){
    ASSERT_EQ(true,this->size == Size());
    ASSERT_EQ(false,this->size == Size(49,50));
    ASSERT_EQ(false,this->size == Size(50,51));
    ASSERT_EQ(false,this->size == Size(3587,18712));
}