#pragma once

#include "Component.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class ComponentTest : public testing::Test{
protected:
	ERModel erModel;
	Component* attribute;
	Component* entity;
	Component* relationShip;
	Component* connector;
	virtual void SetUp();
};