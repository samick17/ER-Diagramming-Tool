#include "ConnectTwoNodesInstruction.h"
#include "Component.h"
#include "RelationType.h"
#include "ControllerEvent.h"

void ConnectTwoNodesInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textPresentation->getAllComponents();
    cout<<"Please enter the first node ID"<<endl;
    Component* firstNode = textPresentation->findComponent();
    cout<<"Please enter the second node ID"<<endl;
    Component* secondNode = textPresentation->findComponent();
    
    int result = textPresentation->connectTwoNodes(firstNode,secondNode);
    
    if(result == NodeConnectionType::ConnectEntityAndRelation)
        this->setCardinality(firstNode,secondNode,textPresentation);
    else if(result == NodeConnectionType::ValidConnect)
        cout<<"The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"' successfully!"<<endl;
    textPresentation->sync(ControllerEvent::ConnectTwoNodes);
}

void ConnectTwoNodesInstruction::setCardinality(Component* firstNode,Component* secondNode,TextPresentation* textPresentation){
    cout<<"The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"'."<<endl;
    cout<<"Enter the type of the cardinality: "<<endl;
    cout<<"[0]1 [1]N"<<endl;
    string cardinality;
    while(true){
        try{
            string input = textPresentation->getInput();
            cardinality = textPresentation->getCardinality(input);
            textPresentation->setCardinality(firstNode,secondNode,cardinality);
            break;
        }
        catch(Exception& exception){
            cout<<exception.what()<<endl;
        }
    }
    cout<<"Its cardinality of the relationship is '"+cardinality+"'."<<endl;
}