#include "DeleteMultiComponentCommandTest.h"

void DeleteMultiComponentCommandTest::SetUp(){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
}

void DeleteMultiComponentCommandTest::TearDown(){
}