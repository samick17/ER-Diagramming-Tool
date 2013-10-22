#pragma once

#include "Document.h"
#include <gtest/gtest.h>

class DocumentTest : public testing::Test{
protected:
	Document* document;
	virtual void SetUp();
	virtual void TearDown();
};