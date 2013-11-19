#include "ReorderComponentsUtilTest.h"
#include "HashMap.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"
#include "StringUtil.h"

void ReorderComponentsUtilTest::SetUp(){
    this->componentMap.put("20",new Attribute("20","testAttribute"));
    this->componentMap.put("16",new Entity("16","testEntity1"));
    this->componentMap.put("34",new Attribute("34","testAttribute2"));
    this->componentMap.put("8",new Entity("8","testEntity2"));
    this->componentMap.put("29",new Connector("29","1"));
    this->componentMap.put("82",new Attribute("82","testAttribute3"));
    this->componentMap.put("0",new RelationShip("0","testRelationShip"));
}

void ReorderComponentsUtilTest::TearDown(){
}

TEST_F(ReorderComponentsUtilTest,testGetReorderedComponentIDMap){
    HashMap<string,string> orderedComponentIDMap = ReorderComponentsUtil::getReorderedComponentIDMap(componentMap);
    
    int index = 0;
    for each(Component* component in this->componentMap){
        ASSERT_EQ(StringUtil::intToString(index),orderedComponentIDMap.get(component->getID()));
        index++;
    }
}