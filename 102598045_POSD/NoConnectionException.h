#pragma once

#include "ComponentException.h"

class NoConnectionException : public ComponentException{
public:
    NoConnectionException(string firstNodeID,string secondNodeID);
    ~NoConnectionException();
};