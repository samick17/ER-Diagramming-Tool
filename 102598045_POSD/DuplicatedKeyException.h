#pragma once

#include "CollectionException.h"

class DuplicatedKeyException : public CollectionException{
public:
	DuplicatedKeyException(string collectionName);
	~DuplicatedKeyException();
};