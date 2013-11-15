#pragma once

#include "Point.h"
#include <gtest/gtest.h>

class PointTest : public testing::Test{
protected:
    Point point;
    virtual void SetUp();
    virtual void TearDown();
};