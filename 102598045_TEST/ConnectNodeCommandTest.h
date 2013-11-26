#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"

class ConnectNodeCommandTest : public testing::Test{
protected:
    Entity* entity;
    Attribute* attribute;
    RelationShip* relationShip;
    ERModel erModel;
    virtual void SetUp();
    virtual void TearDown();
};