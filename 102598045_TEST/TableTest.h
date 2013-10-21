#pragma once

#include "Table.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class TableTest : public testing::Test{
protected:
	ERModel erModel;
	virtual void SetUp();	
};