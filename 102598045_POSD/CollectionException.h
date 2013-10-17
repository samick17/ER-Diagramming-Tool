#pragma once

#include "Exception.h"

class CollectionException : public Exception{
public:
	CollectionException(string collectionName);
	~CollectionException();
};