#pragma once

#include "Exception.h"

class NullPointerException : public Exception{
public:
	NullPointerException();
	~NullPointerException();
};