#pragma once

#include "ComponentTest.h"
#include <gtest/gtest.h>

class NodeTest : public ComponentTest{
protected:
	virtual void SetUp();
	virtual void TearDown();
};