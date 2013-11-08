#pragma once

class ISynchronizer{
public:
    virtual void sync(int syncEventType) = 0;
};