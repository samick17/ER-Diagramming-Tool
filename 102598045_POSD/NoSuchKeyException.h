#pragma once

#include "CollectionException.h"

class NoSuchKeyException : public CollectionException{
public:
	NoSuchKeyException(string collectionName);
	~NoSuchKeyException();
};