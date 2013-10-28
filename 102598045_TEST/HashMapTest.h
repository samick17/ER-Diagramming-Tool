#pragma once

#include "HashMap.h"
#include <gtest/gtest.h>

class HashMapTest : public testing::Test{
protected:
    HashMap<int,string> testMap;
    virtual void SetUp();
    virtual void TearDown();
};