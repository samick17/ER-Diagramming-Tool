#include "AddNodeCommand.h"
#include "ERModel.h"

AddNodeCommand::AddNodeCommand(ERModel* erModel,Node* node) : erModel(erModel),node(node){
}

AddNodeCommand::~AddNodeCommand(){
    if(!this->getExecutionFalg())
        delete this->node;
}

//if ERModel doesn't contains this node, add this node to ERModel
void AddNodeCommand::doExecute(){
    this->erModel->insertComponent(this->node);
}

void AddNodeCommand::doUnExecute(){
    //remove node
    this->erModel->eraseComponent(this->node);
}