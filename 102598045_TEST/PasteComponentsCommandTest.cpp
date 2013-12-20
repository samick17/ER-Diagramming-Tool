#include "PasteComponentsCommandTest.h"

void PasteComponentsCommandTest::SetUp(){
    ASSERT_EQ(0,this->erModel.getAllComponents().size());
}

void PasteComponentsCommandTest::TearDown(){
}