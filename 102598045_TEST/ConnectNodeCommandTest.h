#pragma once

#include <gtest/gtest.h>
#include "HashMap.h"

class Component;
class Entity;
class Attribute;
class RelationShip;

class ConnectNodeCommandTest : public testing::Test{
protected:
    Entity* entity;
    Attribute* attribute;
    RelationShip* relationShip;
    HashMap<string,Component*> componentMap;
    virtual void SetUp();
    virtual void TearDown();
};