#pragma once

#include "GraphicalPresentation.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class GraphicalPresentationTest : public testing::Test{
protected:
    ERModel erModel;
    Presentation* presentation;
    GraphicalPresentation* graphicalPresentation;
    virtual void SetUp();
    virtual void TearDown();
    vector<string>::iterator findComponentIDInVector(vector<string>& componentIDVector,string componentID);
};