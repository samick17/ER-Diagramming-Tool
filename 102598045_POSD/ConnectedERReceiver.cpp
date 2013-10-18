#include "ConnectedERReceiver.h"
#include "StringUtil.h"
#include "SetCardinalityCommand.h"

ConnectedERReceiver::ConnectedERReceiver(int key,Presentation* presentation,Component* firstNode,Component* secondNode) : Receiver(key,presentation),firstNode(firstNode),secondNode(secondNode){
}

ConnectedERReceiver::~ConnectedERReceiver(){
}
/**Non testable function**/
void ConnectedERReceiver::response(){
	Presentation* presentation = this->getPresentation();

	SetCardinalityCommand setCardinalityCommand(presentation,firstNode,secondNode);
	setCardinalityCommand.execute();	
}