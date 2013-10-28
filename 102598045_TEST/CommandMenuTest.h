#pragma once

#include "CommandMenu.h"
#include <gtest/gtest.h>

class CommandMenuTest : public testing::Test{
protected:        
    virtual void SetUp();
    virtual void TearDown();
    CommandMenu commandMenu;
};