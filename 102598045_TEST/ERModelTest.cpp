#include "ERModelTest.h"

ERModelTest::ERModelTest(){
}

ERModelTest::~ERModelTest(){
}

void ERModelTest::SetUp(){
}

void ERModelTest::TearDown(){
}

TEST_F(ERModelTest,clearComponentMap){	
	this->erModel.componentMap.insert(ComponentPair("0",new Entity(ComponentData("0","PC"))));
	ASSERT_EQ(this->erModel.componentMap.empty(),false);
	this->erModel.clearComponentMap();
	ASSERT_EQ(this->erModel.componentMap.empty(),true);
}