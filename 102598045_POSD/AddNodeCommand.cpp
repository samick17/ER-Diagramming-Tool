#include "AddNodeCommand.h"
#include "Node.h"

AddNodeCommand::AddNodeCommand(HashMap<string,Component*>& componentMap,Node* node) : componentMap(componentMap),node(node){
}

AddNodeCommand::~AddNodeCommand(){
    if(!this->getExecutionFalg())
        delete this->node;
}

//if ERModel doesn't contains this node, add this node to ERModel
void AddNodeCommand::doExecute(){
    componentMap.put(this->node->getID(),this->node);
}

void AddNodeCommand::doUnExecute(){
    //remove node
    componentMap.remove(this->node->getID());
}