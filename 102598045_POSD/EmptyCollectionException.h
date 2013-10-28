#pragma once

#include "CollectionException.h"

class EmptyCollectionException : public CollectionException{
public:
    EmptyCollectionException(string collectionName);
    ~EmptyCollectionException();
};