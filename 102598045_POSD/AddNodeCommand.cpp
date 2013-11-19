#include "AddNodeCommand.h"
#include "ERModel.h"
#include "ComponentType.h"
#include "Exception.h"
#include "InvalidNodeTypeException.h"
#include <iostream>

using namespace std;

AddNodeCommand::AddNodeCommand(ERModel* erModel,Node* node) : erModel(erModel),node(node){
}

AddNodeCommand::~AddNodeCommand(){
    if(!this->getExecutionFalg()){
        cout<<"delete node"<<endl;
        delete this->node;
    }
}

//if ERModel doesn't contains this node, add this node to ERModel
void AddNodeCommand::doExecute(){
    this->erModel->insertComponent(this->node);
}

void AddNodeCommand::doUnExecute(){
    //remove node    
    this->erModel->eraseComponent(this->node);
}