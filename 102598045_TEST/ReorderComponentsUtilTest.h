#pragma once

#include "ReorderComponentsUtil.h"
#include <gtest/gtest.h>

class ReorderComponentsUtilTest : public testing::Test{
protected:
	virtual void SetUp();
	virtual void TearDown();
	HashMap<string,Component*> componentMap;
};