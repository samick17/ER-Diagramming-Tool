#pragma once

#include <gtest/gtest.h>
#include "MockCommand.h"

class CommandTest : public testing::Test{
protected:
    MockCommand mockCommand;
    virtual void SetUp();
    virtual void TearDown();
};