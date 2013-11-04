#pragma once

#include "IObserver.h"
#include <string>

using namespace std;

class IObservable{
public:
    virtual void registerObserver(IObserver* observer) = 0;
    virtual void unregisterObserver(IObserver* observer) = 0;
    virtual void notify(int notifiedEventType) = 0;
    virtual void notify(IObserver* observer,int notifiedEventType) = 0;
};