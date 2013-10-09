#include "ConnectionData.h"

ConnectionData::ConnectionData(string connectorID,string connectedFirstNodeID,string connectedSecondNodeID) : connectorID(connectorID),connectedFirstNodeID(connectedFirstNodeID),connectedSecondNodeID(connectedSecondNodeID){
}

ConnectionData::~ConnectionData(){
}

string ConnectionData::getConnectorID(){
	return this->connectorID;
}

string ConnectionData::getConnectedFirstNodeID(){
	return this->connectedFirstNodeID;
}

string ConnectionData::getConnectedSecondNodeID(){
	return this->connectedSecondNodeID;
}