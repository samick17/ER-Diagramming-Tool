#pragma once

#include "ERModel.h"
#include "TextPresentation.h"
#include "CommandManager.h"
#include <gtest/gtest.h>

class IntegrationTest : public testing::Test{
protected:        
    ERModel erModel;
    TextPresentation* textPresentation;
    virtual void SetUp();
    virtual void TearDown();    
    void assertLoadFileCorrectly();
};