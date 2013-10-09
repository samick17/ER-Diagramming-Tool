#pragma once

#include "ComponentException.h"

class HasConnectedException : public ComponentException{
public:
	HasConnectedException(string firstNodeID,string secondNodeID);
	~HasConnectedException();
};