#pragma once

#include "TableManager.h"
#include "RelationShip.h"
#include "Connector.h"
#include "TableUtil.h"
#include <gtest/gtest.h>

class TableUtilTest : public testing::Test{
protected:
    TableManager tableManager;
    HashMap<string,Entity*> entityMap;
    HashMap<string,RelationShip*> relationShipMap;
    HashMap<string,Attribute*> attributeMap;
    HashMap<string,Connector*> connectorMap;
    virtual void SetUp();
    virtual void TearDown();
    void clearAllMap();
};