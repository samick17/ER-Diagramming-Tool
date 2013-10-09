#include "ConnectionReceiverManager.h"
#include "Component.h"
#include "ValidConnectedReceiver.h"
#include "ConnectedERReceiver.h"

ConnectionReceiverManager::ConnectionReceiverManager(Presentation* presentation,Component* firstNode,Component* secondNode){
	Receiver* validConnectedReceiver = new ValidConnectedReceiver(NodeConnectionType::ValidConnect,presentation,firstNode,secondNode);
	Receiver* connectedERReceiver = new ConnectedERReceiver(NodeConnectionType::ConnectEntityAndRelation,presentation,firstNode,secondNode);

	this->insertReceiver(validConnectedReceiver);
	this->insertReceiver(connectedERReceiver);
}

ConnectionReceiverManager::~ConnectionReceiverManager(){
}