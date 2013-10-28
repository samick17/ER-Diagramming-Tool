#pragma once

#include "Exception.h"

class ComponentException : public Exception{
public:
    ComponentException();
    ~ComponentException();
};