#pragma once

#include <gtest/gtest.h>

class DocumentTest : public testing::Test{
protected:
	virtual void SetUp();
	virtual void TearDown();
};