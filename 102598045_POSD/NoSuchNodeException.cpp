#include "NoSuchNodeException.h"

NoSuchNodeException::NoSuchNodeException(string nodeID){
    this->message = "The node ID: '"+nodeID+"' you entered does not exist. Please enter a valid one again.";
}

NoSuchNodeException::~NoSuchNodeException(){
}