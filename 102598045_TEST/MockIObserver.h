#pragma once

#include "IObserver.h"

class MockIObserver : public IObserver{
public:
    void notify(ISubject* subject);
};