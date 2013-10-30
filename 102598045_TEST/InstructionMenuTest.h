#pragma once

#include "InstructionMenu.h"
#include <gtest/gtest.h>

class InstructionMenuTest : public testing::Test{
protected:        
    virtual void SetUp();
    virtual void TearDown();
    InstructionMenu instructionMenu;
};