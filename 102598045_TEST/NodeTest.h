#pragma once

#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class NodeTest : public testing::Test{
protected:
	ERModel erModel;
	Attribute* attribute;
	Entity* entity;
	RelationShip* relationShip;
	virtual void SetUp();
};