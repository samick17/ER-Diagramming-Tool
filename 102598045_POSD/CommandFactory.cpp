#include "CommandFactory.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteMultiComponentCommand.h"
#include "SetPrimaryKeyCommand.h"
#include "EditTextOfComponentsCommand.h"
#include "MoveComponentsCommand.h"
#include "CutComponentsCommand.h"
#include "PasteComponentsCommand.h"

Command* CommandFactory::createAddNodeCommand(HashMap<string,Component*>& componentMap,Node* node){
    return new AddNodeCommand(componentMap,node);
}

Command* CommandFactory::createConnectNodeCommand(HashMap<string,Component*>& componentMap,Component* firstNode,Component* secondNode,Connector* connector){
    return new ConnectNodeCommand(componentMap,firstNode,secondNode,connector);
}

Command* CommandFactory::createDeleteMultiComponentCommand(HashMap<string,Component*>& componentMap,HashMap<string,Component*> componentMapToDelete){
    return new DeleteMultiComponentCommand(componentMap,componentMapToDelete);
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

Command* CommandFactory::createCutComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,HashMap<string,Component*> componentMapToCut){
    return new CutComponentsCommand(componentMap,clipBoard,componentMapToCut);
}

Command* CommandFactory::createPasteComponentsCommand(HashMap<string,Component*>& componentMap,ClipBoard* clipBoard,int* newComponentID,int pasteCount){
    return new PasteComponentsCommand(componentMap,clipBoard,newComponentID,pasteCount);
}