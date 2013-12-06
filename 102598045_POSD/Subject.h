#pragma once

#include <set>
#include <gtest/gtest_prod.h>

class IObserver;

using namespace std;

class Subject{
    friend class SubjectTest;
    FRIEND_TEST(SubjectTest,testRegisterObserver);
    FRIEND_TEST(SubjectTest,testUnregisterObserver);
public:
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);
private:
    set<IObserver*> observerSet;
};