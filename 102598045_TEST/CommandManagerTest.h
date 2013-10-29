#pragma once

#include "CommandManager.h"
#include "TextPresentation.h"
#include "ERModel.h"
#include <gtest/gtest.h>

class CommandManagerTest : public testing::Test{
protected:
	ERModel erModel;
    CommandManager* commandManager;
	Node* entityEngineer;
	Node* entityPC;
	Node* attributeName;
	Node* relationShipHas;
	Connector* connectorEngineerName;
	Connector* connectorHasEngineer;
	Connector* connectorHasPC;
	void executeCommand();
    virtual void SetUp();
    virtual void TearDown();
};