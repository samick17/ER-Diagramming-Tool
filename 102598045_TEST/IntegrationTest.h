#pragma once

#include "ERModel.h"
#include "Presentation.h"
#include "CommandManager.h"
#include <gtest/gtest.h>

class IntegrationTest : public testing::Test{
protected:		
	ERModel erModel;
	Presentation* presentation;
	CommandManager* commandManager;
	virtual void SetUp();
	virtual void TearDown();	
	void assertLoadFileCorrectly();
};