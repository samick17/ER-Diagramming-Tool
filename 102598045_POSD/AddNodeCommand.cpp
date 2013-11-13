#include "AddNodeCommand.h"
#include "ERModel.h"
#include "ComponentType.h"
#include "Exception.h"
#include "InvalidNodeTypeException.h"

using namespace std;

AddNodeCommand::AddNodeCommand(ERModel* erModel,Node* node) : erModel(erModel),node(node){
}

AddNodeCommand::~AddNodeCommand(){
    if(!this->executionFlag){
        delete this->node;
    }
}

//if ERModel doesn't contains this node, add this node to ERModel
void AddNodeCommand::execute(){
    this->erModel->insertComponent(this->node);
    this->executionFlag = true;
}

void AddNodeCommand::unExecute(){
    //remove node    
    this->erModel->eraseComponent(this->node);
    this->executionFlag = false;
}