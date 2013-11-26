#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"

class EditTextOfComponentsCommandTest : public testing::Test{
protected:
    ERModel erModel;
    virtual void SetUp();
    virtual void TearDown();
};