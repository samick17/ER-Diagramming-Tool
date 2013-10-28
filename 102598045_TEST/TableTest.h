#pragma once

#include "Table.h"
#include "Entity.h"
#include <gtest/gtest.h>

class TableTest : public testing::Test{
protected:
    Table* table;
    Entity* entity;
    HashMap<string,Attribute*> attributeMap;
    HashMap<string,Attribute*> foreignKeyAttributeMap;
    virtual void SetUp();
    virtual void TearDown();
    void deleteAndClearHashMap(HashMap<string,Attribute*>& attributeMap);
};