#pragma once

#include "CommandManager.h"
#include "Presentation.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class CommandManagerTest : public testing::Test{
protected:
	CommandManager* commandManager;
	Presentation* presentation;
	ERModel erModel;
	virtual void SetUp();
	virtual void TearDown();
};