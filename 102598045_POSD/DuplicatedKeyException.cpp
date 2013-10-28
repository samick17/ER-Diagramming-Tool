#include "DuplicatedKeyException.h"

DuplicatedKeyException::DuplicatedKeyException(string collectionName) : CollectionException(collectionName){
    this->message = "This collection '"+collectionName+"' has already contains such key!";
}

DuplicatedKeyException::~DuplicatedKeyException(){
}