#pragma once

#include "ComponentFactory.h"
#include <gtest/gtest.h>

class ComponentFactoryTest : public testing::Test{
protected:
    ComponentFactory componentFactory;
    virtual void SetUp();
    virtual void TearDown();    
};