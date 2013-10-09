#pragma once

#include "ComponentException.h"

class InvalidConnectException : public ComponentException{
public:
	InvalidConnectException(string firstNodeID,string secondNodeID);
	~InvalidConnectException();
};