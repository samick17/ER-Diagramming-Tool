#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"

class AddNodeCommandTest : public testing::Test{
protected:
    ERModel erModel;
    virtual void SetUp();
    virtual void TearDown();
};