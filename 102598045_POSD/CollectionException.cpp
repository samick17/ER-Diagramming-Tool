#include "CollectionException.h"

CollectionException::CollectionException(string collectionName){
    this->message = "This collection '"+collectionName+"' occurs some problems!";
}

CollectionException::~CollectionException(){
}