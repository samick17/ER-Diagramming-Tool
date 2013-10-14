#include "ERModelTest.h"
#include "DirectoryUtil.h"

ERModelTest::ERModelTest(){
}

ERModelTest::~ERModelTest(){
}

void ERModelTest::SetUp(){	
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	mkdir(directory.c_str());
}

void ERModelTest::TearDown(){
	string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
	rmdir(directory.c_str());	
}

TEST_F(ERModelTest,clearComponentMap){	
	this->erModel.componentMap.insert(ComponentPair("0",new Entity(ComponentData("0","PC"))));
	ASSERT_EQ(this->erModel.componentMap.empty(),false);
	this->erModel.clearComponentMap();
	ASSERT_EQ(this->erModel.componentMap.empty(),true);
}