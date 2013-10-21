#pragma once

#include "Connector.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class ConnectorTest : public testing::Test{
protected:
	ERModel erModel;
	Component* attribute;
	Component* entity;
	Component* relationShip;
	Connector* connector;
	virtual void SetUp();
};