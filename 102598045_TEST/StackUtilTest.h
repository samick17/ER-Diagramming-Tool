#pragma once

#include <stack>
#include <gtest/gtest.h>

using namespace std;

class StackUtilTest : public testing::Test{
protected:
	stack<int*> integerStack;
	virtual void SetUp();
	virtual void TearDown();
};