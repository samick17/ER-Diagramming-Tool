#pragma once

#include "Presentation.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class PresentationTest : public testing::Test{
protected:
    ERModel erModel;
    Presentation* presentation;
    virtual void SetUp();
    virtual void TearDown();
};