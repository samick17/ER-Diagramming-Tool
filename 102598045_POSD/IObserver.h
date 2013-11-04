#pragma once

#include <string>

using namespace std;

class IObserver{
public:
    virtual void notify(int notifiedEventType) = 0;
};