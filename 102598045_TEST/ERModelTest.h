#pragma once

#include "ERModel.h"
#include <gtest/gtest.h>

class ERModelTest : public testing::Test{
protected:        
    ERModel erModel;
    bool hasConnected(Component* firstComponent,Component* secondComponent);    
    virtual void SetUp();    
};