#pragma once

#include "CommandFactory.h"
#include <gtest/gtest.h>

class CommandFactoryTest : public testing::Test{
protected:
    CommandFactory commandFactory;
    virtual void SetUp();
    virtual void TearDown();
};