#pragma once

#include "RelationShip.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class RelationShipTest : public testing::Test{
protected:
	ERModel erModel;
	Component* attribute;
	Component* entity;
	RelationShip* relationShip;
	virtual void SetUp();
	virtual void TearDown();
};