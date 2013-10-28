#pragma once

#include "ComponentTest.h"
#include <gtest/gtest.h>

class ConnectorTest : public ComponentTest{
protected:
    virtual void SetUp();
    virtual void TearDown();
};