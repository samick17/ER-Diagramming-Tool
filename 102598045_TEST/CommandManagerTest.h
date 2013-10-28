#pragma once

#include "CommandManager.h"
#include "TextPresentation.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class CommandManagerTest : public testing::Test{
protected:
    CommandManager commandManager;
    virtual void SetUp();
    virtual void TearDown();
};