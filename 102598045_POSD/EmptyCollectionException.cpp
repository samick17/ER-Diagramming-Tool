#include "EmptyCollectionException.h"

EmptyCollectionException::EmptyCollectionException(string collectionName){
	this->message = "It has no "+collectionName+"!";
}

EmptyCollectionException::~EmptyCollectionException(){
}