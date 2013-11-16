#pragma once

#include "Rect.h"
#include <gtest/gtest.h>

class RectTest : public testing::Test{
protected:
    Rect rect;
    virtual void SetUp();
    virtual void TearDown();
};