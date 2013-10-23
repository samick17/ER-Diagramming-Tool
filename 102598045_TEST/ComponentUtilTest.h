#pragma once

#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include <gtest/gtest.h>

class ComponentUtilTest : public testing::Test{
protected:
	Attribute* attribute;
	Entity* entity;
	RelationShip* relationShip;
	Connector* connector1;
	Connector* connector2;
	virtual void SetUp();
	virtual void TearDown();
};