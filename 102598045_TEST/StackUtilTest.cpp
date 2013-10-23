#include "StackUtilTest.h"
#include "StackUtil.h"

void StackUtilTest::SetUp(){
	integerStack.push(new int(1));
	integerStack.push(new int(10071));
	integerStack.push(new int(261));
	integerStack.push(new int(7468));
	integerStack.push(new int(395));
	integerStack.push(new int(6472));
	integerStack.push(new int(1258614));
}

void StackUtilTest::TearDown(){
}

TEST_F(StackUtilTest,testDeleteAllElementsInStack){
	ASSERT_EQ(7,this->integerStack.size());
	StackUtil::deleteAllElementsInStack<int>(this->integerStack);
	ASSERT_EQ(0,this->integerStack.size());
}

TEST_F(StackUtilTest,testPop){
	ASSERT_EQ(7,this->integerStack.size());
	ASSERT_EQ(1258614,*StackUtil::pop<int>(this->integerStack));
	ASSERT_EQ(6,this->integerStack.size());
	ASSERT_EQ(6472,*StackUtil::pop<int>(this->integerStack));
	ASSERT_EQ(5,this->integerStack.size());
	ASSERT_EQ(395,*StackUtil::pop<int>(this->integerStack));
	ASSERT_EQ(4,this->integerStack.size());
	ASSERT_EQ(7468,*StackUtil::pop<int>(this->integerStack));
	ASSERT_EQ(3,this->integerStack.size());
	ASSERT_EQ(261,*StackUtil::pop<int>(this->integerStack));	
	ASSERT_EQ(2,this->integerStack.size());
	ASSERT_EQ(10071,*StackUtil::pop<int>(this->integerStack));
	ASSERT_EQ(1,this->integerStack.size());
	ASSERT_EQ(1,*StackUtil::pop<int>(this->integerStack));	
	ASSERT_EQ(0,this->integerStack.size());
	ASSERT_THROW(StackUtil::pop<int>(this->integerStack),EmptyCollectionException);
}