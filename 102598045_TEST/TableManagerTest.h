#pragma once

#include "TableManager.h"
#include <gtest/gtest.h>

class TableManagerTest : public testing::Test{
protected:
    TableManager tableManager;
    virtual void SetUp();
    virtual void TearDown();
};