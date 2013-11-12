#pragma once

#include "ISynchronizer.h"

class ISyncable{
public:
    virtual void registerSynchronizer(ISynchronizer* synchronizer) = 0;
    virtual void unregisterSynchronizer(ISynchronizer* synchronizer) = 0;
    virtual void sync(int syncEventType) = 0;
    //virtual void sync(ISynchronizer* synchronizer,int syncEventType) = 0;
};