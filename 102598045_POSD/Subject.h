#pragma once

#include "ISubject.h"
#include <set>
#include <gtest/gtest_prod.h>

using namespace std;

class Subject : public ISubject{
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