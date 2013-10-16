#pragma once

#include "Connector.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class ConnectorTest : public testing::Test{
protected:
	ERModel erModel;
	Connector* connector;
	virtual void SetUp();
	virtual void TearDown();
};