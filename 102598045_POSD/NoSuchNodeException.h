#pragma once

#include "Exception.h"

class NoSuchNodeException : public Exception{
public:
    NoSuchNodeException(string nodeID);
    ~NoSuchNodeException();
};