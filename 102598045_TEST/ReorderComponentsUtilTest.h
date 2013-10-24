#pragma once

#include "ReorderComponentsUtil.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class ReorderComponentsUtilTest : public testing::Test{
protected:
	ERModel erModel;
	virtual void SetUp();
	virtual void TearDown();
};