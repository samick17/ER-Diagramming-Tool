#include "NoConnectionException.h"

NoConnectionException::NoConnectionException(string componentID){
    this->message = "The node '"+componentID+"' does not belong to any Entity. Please enter a valid one again.";
}

NoConnectionException::~NoConnectionException(){
}