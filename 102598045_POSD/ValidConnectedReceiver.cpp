#include "ValidConnectedReceiver.h"

ValidConnectedReceiver::ValidConnectedReceiver(int key,Presentation* presentation,Component* firstNode,Component* secondNode) : Receiver(key,presentation),firstNode(firstNode),secondNode(secondNode){
}

ValidConnectedReceiver::~ValidConnectedReceiver(){
}
/**Non testable function**/
void ValidConnectedReceiver::response(){
	Presentation* presentation = this->getPresentation();

	presentation->logMessage("The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"' successfully!",true);	
	presentation->displayConnections();
}