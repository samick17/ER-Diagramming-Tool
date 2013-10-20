#pragma once

#include "Attribute.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class AttributeTest : public testing::Test{
protected:
	ERModel erModel;
	Attribute* attribute;
	Component* entity;
	Component* relationShip;
	virtual void SetUp();
	virtual void TearDown();
};