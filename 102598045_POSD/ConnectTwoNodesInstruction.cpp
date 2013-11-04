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
	textPresentation->notify(ControllerEvent::ConnectTwoNodes);
}

void ConnectTwoNodesInstruction::setCardinality(Component* firstNode,Component* secondNode,TextPresentation* textPresentation){
    HashMap<string,string> cardinalityPairMap;
    cardinalityPairMap.put("0",RelationType::OneToOne);
    cout<<"Enter the type of the cardinality: "<<endl;
    cout<<"[0]1 [1]N"<<endl;
    cout<<"The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"'."<<endl;
    string input = textPresentation->getInput();

    while(!cardinalityPairMap.containsKey(input)){
        cout<<"the cardinality you entered doesn't exist. Please entered a valid one again"<<endl;
        input = textPresentation->getInput();
    }
    string relationName = cardinalityPairMap.get(input);
    textPresentation->setCardinality(firstNode,secondNode,relationName);
    cout<<"Its cardinality of the relationship is '"+relationName+"'."<<endl;
}