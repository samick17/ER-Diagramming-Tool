#pragma once

#include "AddNodeState.h"
#include "ERModel.h"
#include "Presentation.h"
#include "GraphicalPresentation.h"
#include <gtest/gtest.h>

class AddNodeStateTest : public testing::Test{
protected:
    AddNodeState* addNodeState;
    ERModel erModel;
    Presentation* presentation;
    GraphicalPresentation* graphicalPresentation;
    virtual void SetUp();
    virtual void TearDown();
};