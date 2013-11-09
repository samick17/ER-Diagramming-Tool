#pragma once

class IObserver;

class ISubject{
public:
    virtual void registerObserver(IObserver* observer) = 0;
    virtual void unregisterObserver(IObserver* observer) = 0;
    virtual void notify() = 0;
    virtual void notify(IObserver* observer) = 0;
};