#pragma once

#include "ComponentException.h"

class ConnectedSelfException : public ComponentException{
public:
    ConnectedSelfException(string nodeID);
    ~ConnectedSelfException();
};