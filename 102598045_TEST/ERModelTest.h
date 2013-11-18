#pragma once

#include "ERModel.h"
#include <gtest/gtest.h>

class ERModelTest : public testing::Test{
protected:
    ERModel erModel;
    Presentation* presentation;
    TextPresentation* textPresentation;
    TextUIPresenter* textUIPresenter;
    bool hasConnected(Component* firstComponent,Component* secondComponent);
    virtual void SetUp();
    virtual void TearDown();
};