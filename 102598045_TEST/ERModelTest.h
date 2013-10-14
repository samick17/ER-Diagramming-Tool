#pragma once

#include "..\102598045_POSD\ERModel.h"
#include <gtest/gtest.h>

class ERModelTest : public testing::Test{
public:
	ERModelTest();
	~ERModelTest();
protected:	
	virtual void SetUp();
	virtual void TearDown();
	ERModel erModel;
};