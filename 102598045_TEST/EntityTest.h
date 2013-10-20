#pragma once

#include "Entity.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class EntityTest : public testing::Test{
protected:
	ERModel erModel;
	Component* attribute;
	Entity* entity;
	Component* relationShip;
	virtual void SetUp();
	virtual void TearDown();
};