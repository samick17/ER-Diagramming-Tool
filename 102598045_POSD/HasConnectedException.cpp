#include "HasConnectedException.h"

HasConnectedException::HasConnectedException(string firstNodeID,string secondNodeID){
	this->message = "The node '"+firstNodeID+"' has already been connected to the node "+secondNodeID+".";
}

HasConnectedException::~HasConnectedException(){
}