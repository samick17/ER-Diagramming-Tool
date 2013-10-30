#include "AddNodeInstruction.h"
#include "Node.h"
#include "ComponentType.h"
#include "InvalidNodeTypeException.h"

AddNodeInstruction::AddNodeInstruction(){
}

AddNodeInstruction::~AddNodeInstruction(){
}

void AddNodeInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    cout<<"What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation"<<endl;
    Node* node = this->addNode(textPresentation);
	//set Node Name
    cout<<"Enter the name of this node:"<<endl;
    string input = textPresentation->getInput();
    //node name out of range
    while(input.size() >= TABLE_WIDTH){
        cout<<"The name you entered is too long,please enter a concise one again."<<endl;
        input = textPresentation->getInput();
    }
    node->setName(input);
    cout<<"A node ["+node->getClassName()+"] has been added. ID: "+node->getID()+",Name: "+node->getName()<<endl;
    textUIPresenter->displayComponents();
}

Node* AddNodeInstruction::addNode(TextPresentation* textPresentation){
    Node* node = NULL;
    while(node == NULL){
        try{
            string input = textPresentation->getInput();
            if(input == ComponentType::TypeConnector)
                throw InvalidNodeTypeException();
            node = textPresentation->addNode(input);
        }
        catch(Exception& exception){
            cout<<exception.getMessage()<<endl;
        }
    }
    return node;
}