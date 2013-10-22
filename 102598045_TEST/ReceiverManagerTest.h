#pragma once

#include "ReceiverManager.h"
#include "ERModel.h"
#include "Presentation.h"
#include <gtest/gtest.h>

class ReceiverManagerTest : public testing::Test{
protected:
	ReceiverManager receiverManager;
	ERModel erModel;
	Presentation* presentation;
	virtual void SetUp();
	virtual void TearDown();
};