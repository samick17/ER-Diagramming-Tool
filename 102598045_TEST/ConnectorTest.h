#pragma once

#include "Connector.h"
#include <gtest/gtest.h>

class ConnectorTest : public testing::Test{
protected:	
	Connector* connector;
	virtual void SetUp();
	virtual void TearDown();
};