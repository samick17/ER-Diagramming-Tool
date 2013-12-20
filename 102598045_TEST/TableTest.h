#pragma once

#include "Table.h"
#include "Entity.h"
#include <gtest/gtest.h>

class TableTest : public testing::Test{
protected:
    Table* table;
    Entity* entity;
    HashMap<string,Attribute*> primaryKeyAttributeMap;
    HashMap<string,Attribute*> defaultAttributeMap;
    HashMap<string,Attribute*> foreignKeyAttributeMap;
    virtual void SetUp();
    virtual void TearDown();
};