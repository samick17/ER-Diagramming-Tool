#include "InvalidNodeTypeException.h"

InvalidNodeTypeException::InvalidNodeTypeException(){
    this->message = "You entered an invalid node type. Please enter a valid one again.";
}

InvalidNodeTypeException::~InvalidNodeTypeException(){
}