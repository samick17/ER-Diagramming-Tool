#pragma once

#include "ERModel.h"
#include "Presentation.h"
#include "GraphicalPresentation.h"
#include <gtest/gtest.h>

class StateTest : public testing::Test{
protected:
    ERModel erModel;
    Presentation* presentation;
    GraphicalPresentation* graphicalPresentation;
    virtual void SetUp();
    virtual void TearDown();
};