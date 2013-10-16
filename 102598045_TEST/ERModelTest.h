#pragma once

#include "ERModel.h"
#include <gtest/gtest.h>

class ERModelTest : public testing::Test{
protected:	
	ERModel erModel;
	virtual void SetUp();
	virtual void TearDown();	
	bool hasConnected(Component* firstComponent,Component* secondComponent);	
};