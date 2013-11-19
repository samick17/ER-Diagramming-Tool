#pragma once

#include "CommandFactory.h"
#include <gtest/gtest.h>

class CommandFactoryTest : public testing::Test{
protected:
    virtual void SetUp();
    virtual void TearDown();
};