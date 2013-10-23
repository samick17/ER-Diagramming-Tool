#include "StringUtilTest.h"
#include "StringUtil.h"

void StringUtilTest::SetUp(){}

void StringUtilTest::TearDown(){}

TEST_F(StringUtilTest,testIntToString){
	ASSERT_EQ("7726",StringUtil::intToString(7726));
	ASSERT_EQ("24985",StringUtil::intToString(24985));
	ASSERT_EQ("0",StringUtil::intToString(0));
	ASSERT_EQ("-1",StringUtil::intToString(-1));
}

TEST_F(StringUtilTest,testplit){
	string stringToSplit = "a 123  456";
	vector<string> stringSplitted = StringUtil::split(stringToSplit,' ');
	ASSERT_EQ(4,stringSplitted.size());
	ASSERT_EQ("a",stringSplitted[0]);
	ASSERT_EQ("123",stringSplitted[1]);
	ASSERT_EQ("",stringSplitted[2]);
	ASSERT_EQ("456",stringSplitted[3]);
	stringToSplit = "a 123,456";
	stringSplitted = StringUtil::split(stringToSplit,',');
	ASSERT_EQ(2,stringSplitted.size());
	ASSERT_EQ("a 123",stringSplitted[0]);
	ASSERT_EQ("456",stringSplitted[1]);
}

TEST_F(StringUtilTest,testTrimStart){
	string stringToTrimStart = "   123Test  ";
	ASSERT_EQ("123Test  ",StringUtil::trimStart(stringToTrimStart));
	stringToTrimStart = ",   t e s  t B  ";
	ASSERT_EQ(",   t e s  t B  ",StringUtil::trimStart(stringToTrimStart));
}

TEST_F(StringUtilTest,testTrimEnd){
	string stringToTrimEnd = "   T E  S T !  !   !  !    ";
	ASSERT_EQ("   T E  S T !  !   !  !",StringUtil::trimEnd(stringToTrimEnd));
	stringToTrimEnd = "   *   & ^  !  ^  &  %  #";
	ASSERT_EQ("   *   & ^  !  ^  &  %  #",StringUtil::trimEnd(stringToTrimEnd));
}

TEST_F(StringUtilTest,testTrim){
	string stringToTrim = "   ,test, )(##!!;  ";
	ASSERT_EQ(",test, )(##!!;",StringUtil::trim(stringToTrim));
	stringToTrim = "T E S T Trim";
	ASSERT_EQ("T E S T Trim",StringUtil::trim(stringToTrim));
}

TEST_F(StringUtilTest,testAppendWithComma){
	vector<string> stringVector;
	stringVector.push_back("first");
	stringVector.push_back("second,");
	stringVector.push_back(",third,");	
	ASSERT_EQ("first,second,,,third,",StringUtil::appendWithComma(stringVector));
	stringVector.clear();
	stringVector.push_back(" testA ");
	stringVector.push_back(" testB ");
	stringVector.push_back(" testC ");	
	ASSERT_EQ(" testA , testB , testC ",StringUtil::appendWithComma(stringVector));
}