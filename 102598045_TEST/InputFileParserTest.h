#pragma once

#include "InputFileParser.h"
#include <gtest/gtest.h>

class InputFileParserTest : public testing::Test{
protected:
    ERModel erModel;
    InputFileParser inputFileParser;
    Document* document;
    virtual void SetUp();
    virtual void TearDown();
};