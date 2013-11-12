#pragma once

#include "ISubject.h"
#include <set>

using namespace std;

class Subject : public ISubject{
public:
    void registerObserver(IObserver* observer);
    void unregisterObserver(IObserver* observer);
    void notify();
    void notify(IObserver* observer);
protected:
    virtual void doRegisterObserver(IObserver* observer);
    virtual void doUngisterObserver(IObserver* observer);
private:
    set<IObserver*> observerSet;
};