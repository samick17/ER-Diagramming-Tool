#include "CommandFactory.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteMultiComponentCommand.h"
#include "SetPrimaryKeyCommand.h"
#include "EditTextOfComponentsCommand.h"
#include "MoveComponentsCommand.h"

Command* CommandFactory::createAddNodeCommand(ERModel* erModel,Node* node){
    return new AddNodeCommand(erModel,node);
}

Command* CommandFactory::createConnectNodeCommand(ERModel* erModel,Component* firstNode,Component* secondNode,Connector* connector){
    return new ConnectNodeCommand(erModel,firstNode,secondNode,connector);
}

Command* CommandFactory::createDeleteMultiComponentCommand(ERModel* erModel,vector<string> componentIDVector){
    return new DeleteMultiComponentCommand(erModel,componentIDVector);
}

Command* CommandFactory::createSetPrimaryKeyCommand(Attribute* attribute){
    return new SetPrimaryKeyCommand(attribute);
}

Command* CommandFactory::createEditTextOfComponentsCommand(Component* component,string text){
    return new EditTextOfComponentsCommand(component,text);
}

Command* CommandFactory::createMoveComponentsCommand(HashMap<string,Component*> selectedComponentMap,Point mousePressPosition,Point mouseReleasePosition){
    return new MoveComponentsCommand(selectedComponentMap,mousePressPosition,mouseReleasePosition);
}