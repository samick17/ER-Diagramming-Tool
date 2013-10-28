#include "NoConnectionException.h"

NoConnectionException::NoConnectionException(string firstNodeID,string secondNodeID){
    this->message = "The node '"+firstNodeID+"' does not belong to Entity '"+secondNodeID+"'. Please enter a valid one again.";
}

NoConnectionException::~NoConnectionException(){
}