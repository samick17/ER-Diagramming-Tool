#pragma once

#include "Attribute.h"
#include "RelationShip.h"
#include "Entity.h"
#include "Connector.h"
#include <gtest/gtest.h>

class AttributeTest : public testing::Test{
protected:
	//ERModel erModel;
	Attribute* attribute;
	Entity* entity;
	RelationShip* relationShip;
	virtual void SetUp();
	virtual void TearDown();
	void connectWithEachOther(Node* firstNode,Node* secondNode,Connector* connector);
};