#pragma once

#include "TextPresentation.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class TextPresentationTest : public testing::Test{
protected:
    ERModel erModel;
    Presentation* presentation;
    TextPresentation* textPresentation;
    virtual void SetUp();
    virtual void TearDown();
};