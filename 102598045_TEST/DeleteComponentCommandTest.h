#pragma once

#include <gtest/gtest.h>
#include "HashMap.h"

class Component;

class DeleteComponentCommandTest : public testing::Test{
protected:
    HashMap<string,Component*> componentMap;
    void connectTwoNodes(string componentID,Component* sourceComponent,Component* targetComponent);
    virtual void SetUp();
    virtual void TearDown();
};