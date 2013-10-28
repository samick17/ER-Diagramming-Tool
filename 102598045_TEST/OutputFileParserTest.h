#pragma once

#include "OutputFileParser.h"
#include <gtest/gtest.h>

class OutputFileParserTest : public testing::Test{
protected:
    OutputFileParser* outputFileParser;
    Document* document;
    HashMap<string,Component*> componentMap;
    void insertComponentMap(Component* component);
    virtual void SetUp();
    virtual void TearDown();
};