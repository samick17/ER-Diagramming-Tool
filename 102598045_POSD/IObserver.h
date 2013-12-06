#pragma once

class Subject;

class IObserver{
public:
    virtual void notify(Subject* subject) = 0;
};