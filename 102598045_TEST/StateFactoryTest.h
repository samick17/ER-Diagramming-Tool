#pragma once

#include "StateFactory.h"
#include <gtest/gtest.h>

class StateFactoryTest : public testing::Test{
protected:
    StateFactory stateFactory;
    virtual void SetUp();
    virtual void TearDown();
};