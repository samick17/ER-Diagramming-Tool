#include "NoSuchKeyException.h"

NoSuchKeyException::NoSuchKeyException(string collectionName) : CollectionException(collectionName){
	this->message = "This collection '"+collectionName+"' doesn't contains such key!";
}

NoSuchKeyException::~NoSuchKeyException(){
}