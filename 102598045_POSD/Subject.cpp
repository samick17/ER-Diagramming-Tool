#include "Subject.h"
#include "IObserver.h"

void Subject::registerObserver(IObserver* observer){
    this->observerSet.insert(observer);
    this->doRegisterObserver(observer);
}

void Subject::unregisterObserver(IObserver* observer){
    this->observerSet.erase(observer);
    this->doUngisterObserver(observer);
}

void Subject::notify(){
    for each(IObserver* observer in this->observerSet)
        this->notify(observer);
}

void Subject::notify(IObserver* observer){
    observer->notify(this);
}

void Subject::doRegisterObserver(IObserver* observer){
}

void Subject::doUngisterObserver(IObserver* observer){
}