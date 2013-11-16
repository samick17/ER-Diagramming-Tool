#include "HashMapTest.h"

void HashMapTest::SetUp(){}

void HashMapTest::TearDown(){}

TEST_F(HashMapTest,testHashMap){
    ASSERT_EQ(0,testMap.size());
    
    //Assert empty
    ASSERT_EQ(true,testMap.empty());
    int key1 = 0;
    string string1 = "test1";
    ASSERT_EQ(string1,testMap.put(key1,string1));
    ASSERT_EQ(string1,testMap.get(key1));
    ASSERT_EQ(1,testMap.size());
    ASSERT_EQ(string1,testMap.getValueByIndex(0));
    ASSERT_EQ(true,testMap.containsKey(key1));
    ASSERT_EQ(false,testMap.empty());
    ASSERT_EQ(0,testMap.getValueIndex(string1));

    int key2 = 4;
    string string2 = "testLine2";
    ASSERT_EQ(string2,testMap.put(key2,string2));
    ASSERT_EQ(string2,testMap.get(key2));
    ASSERT_EQ(2,testMap.size());
    ASSERT_EQ(string2,testMap.getValueByIndex(1));
    ASSERT_EQ(true,testMap.containsKey(key2));
    ASSERT_EQ(1,testMap.getValueIndex(string2));

    int key3 = 13;
    string string3 = "third";
    ASSERT_EQ(string3,testMap.put(key3,string3));
    ASSERT_EQ(string3,testMap.get(key3));
    ASSERT_EQ(3,testMap.size());
    ASSERT_EQ(string3,testMap.getValueByIndex(2));
    ASSERT_EQ(true,testMap.containsKey(key3));
    ASSERT_EQ(2,testMap.getValueIndex(string3));
    //test for each
    string result = "";
    for each(string str in testMap)
        result += str;
    ASSERT_EQ(result,string1+string2+string3);
    result = "";
    for(HashMap<int,string>::reverse_iterator reverseIterator = testMap.rbegin();reverseIterator != testMap.rend();reverseIterator++)
        result += *reverseIterator;
    ASSERT_EQ(result,string3+string2+string1);

    //insert at index1
    int key4 = 7;
    string string4 = "insertTest";
    ASSERT_EQ(string4,testMap.insertAt(key4,string4,1));
    ASSERT_EQ(4,testMap.size());
    ASSERT_EQ(string4,testMap.get(key4));
    ASSERT_EQ(string4,testMap.getValueByIndex(1));
    ASSERT_EQ(true,testMap.containsKey(key4));

    ASSERT_EQ(0,testMap.getValueIndex(string1));
    ASSERT_EQ(2,testMap.getValueIndex(string2));
    ASSERT_EQ(3,testMap.getValueIndex(string3));
    ASSERT_EQ(1,testMap.getValueIndex(string4));
    
    ASSERT_EQ(false,testMap.containsKey(-1));
    ASSERT_EQ(false,testMap.containsKey(3));
    ASSERT_EQ(false,testMap.containsKey(5));
    ASSERT_EQ(false,testMap.empty());

    //test for each
    result = "";
    for each(string str in testMap)
        result += str;
    ASSERT_EQ(result,string1+string4+string2+string3);
    result = "";
    for(HashMap<int,string>::reverse_iterator reverseIterator = testMap.rbegin();reverseIterator != testMap.rend();reverseIterator++)
        result += *reverseIterator;
    ASSERT_EQ(result,string3+string2+string4+string1);

    testMap.clear();
    //Assert empty
    ASSERT_EQ(true,testMap.empty());
}