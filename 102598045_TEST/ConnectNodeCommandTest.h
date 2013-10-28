#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"
#include "TextPresentation.h"

class ConnectNodeCommandTest : public testing::Test{
protected:
	Entity* entity;
	Attribute* attribute;
	RelationShip* relationShip;
    ERModel erModel;
    TextPresentation* textPresentation;
    virtual void SetUp();
    virtual void TearDown();
};