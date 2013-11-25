#pragma once

#include "ComponentException.h"

class NoConnectionException : public ComponentException{
public:
    NoConnectionException(string componentID);
    ~NoConnectionException();
};