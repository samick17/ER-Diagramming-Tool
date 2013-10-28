#pragma once

#include "Exception.h"

class InvalidNodeTypeException : public Exception{
public:
    InvalidNodeTypeException();
    ~InvalidNodeTypeException();
};