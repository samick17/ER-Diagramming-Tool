#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"
#include "TextPresentation.h"

class AddNodeCommandTest : public testing::Test{
protected:
    ERModel erModel;
    TextPresentation* textPresentation;
    virtual void SetUp();
    virtual void TearDown();
};