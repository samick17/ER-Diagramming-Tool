#pragma once

#include "Attribute.h"
#include "RelationShip.h"
#include "Entity.h"
#include "Connector.h"
#include <gtest/gtest.h>

class ComponentTest : public testing::Test{
protected:
	Attribute* attribute;
	Entity* entity;
	RelationShip* relationShip;
	Connector* connector;
	virtual void SetUp();
	virtual void TearDown();
	void connectWithEachOther(Node* firstNode,Node* secondNode,Connector* connector);
};