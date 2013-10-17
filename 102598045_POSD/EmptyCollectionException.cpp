#include "EmptyCollectionException.h"

EmptyCollectionException::EmptyCollectionException(string collectionName) : CollectionException(collectionName){
	this->message = "It has no "+collectionName+"!";
}

EmptyCollectionException::~EmptyCollectionException(){
}