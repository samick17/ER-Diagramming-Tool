#pragma once

#include "ConnectState.h"
#include "ERModel.h"
#include "Presentation.h"
#include "GraphicalPresentation.h"
#include <gtest/gtest.h>

class ConnectStateTest : public testing::Test{
protected:
    ConnectState* connectState;
    ERModel erModel;
    Presentation* presentation;
    GraphicalPresentation* graphicalPresentation;
    virtual void SetUp();
    virtual void TearDown();
};