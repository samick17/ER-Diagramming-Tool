#pragma once

#include "Exception.h"

class EmptyCollectionException : public Exception{
public:
	EmptyCollectionException(string collectionName);
	~EmptyCollectionException();
};