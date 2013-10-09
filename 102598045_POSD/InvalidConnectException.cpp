#include "InvalidConnectException.h"

InvalidConnectException::InvalidConnectException(string firstNodeID,string secondNodeID){
	this->message = "The node '"+firstNodeID+"' cannot be connected by the node "+secondNodeID+".";
}

InvalidConnectException::~InvalidConnectException(){
}