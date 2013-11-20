#include "SubjectTest.h"
#include "MockIObserver.h"

void SubjectTest::SetUp(){
    ASSERT_EQ(0,this->subject.observerSet.size());
}

void SubjectTest::TearDown(){
}

TEST_F(SubjectTest,testRegisterObserver){
    MockIObserver observer1;
    this->subject.registerObserver(&observer1);
    ASSERT_EQ(1,this->subject.observerSet.size());
    this->subject.registerObserver(&observer1);
    ASSERT_EQ(1,this->subject.observerSet.size());
    MockIObserver observer2;
    this->subject.registerObserver(&observer2);
    ASSERT_EQ(2,this->subject.observerSet.size());
}

TEST_F(SubjectTest,testUnregisterObserver){
    MockIObserver observer1;
    MockIObserver observer2;
    this->subject.observerSet.insert(&observer1);
    this->subject.unregisterObserver(NULL);
    ASSERT_EQ(1,this->subject.observerSet.size());
    this->subject.unregisterObserver(&observer1);
    ASSERT_EQ(0,this->subject.observerSet.size());
    this->subject.observerSet.insert(&observer1);
    ASSERT_EQ(1,this->subject.observerSet.size());
    this->subject.observerSet.insert(&observer2);
    ASSERT_EQ(2,this->subject.observerSet.size());
    this->subject.unregisterObserver(&observer1);
    ASSERT_EQ(1,this->subject.observerSet.size());
    this->subject.unregisterObserver(&observer2);
    ASSERT_EQ(0,this->subject.observerSet.size());
}