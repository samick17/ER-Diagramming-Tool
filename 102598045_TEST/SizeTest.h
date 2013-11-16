#pragma once

#include "Size.h"
#include <gtest/gtest.h>

class SizeTest : public testing::Test{
protected:
    Size size;
    virtual void SetUp();
    virtual void TearDown();
};