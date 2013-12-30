#pragma once

#include <gtest/gtest.h>
#include "SaveComponentVisitor.h"

class Node;
class Connector;

class SaveComponentVisitorTest : public testing::Test{
protected:
    void connectWithEachOther(Node* sourceNode,Node* targetNode,Connector* connector);
    virtual void SetUp();
    virtual void TearDown();
};