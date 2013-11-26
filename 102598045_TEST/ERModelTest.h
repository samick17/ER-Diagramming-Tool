#pragma once

#include "ERModel.h"
#include <gtest/gtest.h>

class TextPresentation;
class Presentation;

class ERModelTest : public testing::Test{
protected:
    ERModel erModel;
    Presentation* presentation;
    TextPresentation* textPresentation;
    bool hasConnected(Component* firstComponent,Component* secondComponent);
    virtual void SetUp();
    virtual void TearDown();
};