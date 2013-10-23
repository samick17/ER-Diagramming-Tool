#pragma once

#include "ReorderComponentsUtil.h"
#include <gtest/gtest.h>

class ReorderComponentsUtilTest : public testing::Test{
protected:
	ReorderComponentsUtil reorderComponentUtil;
	ERModel erModel;
	virtual void SetUp();
	virtual void TearDown();
};