#pragma once

#include "QActionData.h"
#include <gtest/gtest.h>

class QActionDataTest : public testing::Test{
protected:
    virtual void SetUp();
    virtual void TearDown();
    string expectedToolTip(string name,string key);
};