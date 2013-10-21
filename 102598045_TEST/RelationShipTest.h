#pragma once

#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
//#include "ERModel.h"
#include <gtest/gtest.h>

class RelationShipTest : public testing::Test{
protected:
	//ERModel erModel;
	Attribute* attribute;
	Entity* entity;
	RelationShip* relationShip;
	virtual void SetUp();
	virtual void TearDown();
	void connectWithEachOther(Node* firstNode,Node* secondNode,Connector* connector);
};