#pragma once

class ISubject;

class IObserver{
public:
    virtual void notify(ISubject* subject) = 0;
};