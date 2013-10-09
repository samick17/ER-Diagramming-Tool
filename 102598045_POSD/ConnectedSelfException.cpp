#include "ConnectedSelfException.h"

ConnectedSelfException::ConnectedSelfException(string nodeID){
	this->message = "The node '"+nodeID+"' cannot be connected to itself.";
}

ConnectedSelfException::~ConnectedSelfException(){
}