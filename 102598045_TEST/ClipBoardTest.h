#pragma once

#include "ClipBoard.h"
#include <gtest/gtest.h>

class ClipBoardTest : public testing::Test{
protected:
    virtual void SetUp();
    virtual void TearDown();
};