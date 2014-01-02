#pragma once

#include <gtest/gtest.h>
#include "HashMap.h"

class Component;

class CutComponentsCommandTest : public testing::Test{
protected:
    HashMap<string,Component*> componentMap;
    virtual void SetUp();
    virtual void TearDown();
};