#pragma once

class ISynchronizer{
public:
    virtual void sync(string syncEventType) = 0;
};