#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"
#include "Presentation.h"

class AddNodeCommandTest : public testing::Test{
protected:
	ERModel erModel;
	Presentation* presentation;
	virtual void SetUp();
	virtual void TearDown();
};