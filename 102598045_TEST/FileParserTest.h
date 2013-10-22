#pragma once

#include "FileParser.h"
#include <gtest/gtest.h>

class FileParserTest : public testing::Test{
protected:
	ERModel erModel;
	FileParser fileParser;
	Document* document;
	virtual void SetUp();
	virtual void TearDown();
};