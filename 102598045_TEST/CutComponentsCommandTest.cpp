#include "CutComponentsCommandTest.h"

void CutComponentsCommandTest::SetUp(){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
}

void CutComponentsCommandTest::TearDown(){
}