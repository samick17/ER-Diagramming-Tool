#include "ComponentDataTest.h"

void ComponentDataTest::SetUp(){
}

void ComponentDataTest::TearDown(){
}

TEST_F(ComponentDataTest,testEquals){
    ComponentData componentData = ComponentData("","0","Entity");
    ASSERT_EQ(true,componentData == componentData);
    ASSERT_EQ(false,componentData == ComponentData("","0","Entit"));
    ASSERT_EQ(false,componentData == ComponentData("","1","Entity"));
    ASSERT_EQ(false,componentData == ComponentData("","5","Relation"));
}