#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include "Node.h"

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
    stateToNodeTypeMap.put(StateID::AttributeState,ComponentType::TypeAttribute);
    stateToNodeTypeMap.put(StateID::EntityState,ComponentType::TypeEntity);
    stateToNodeTypeMap.put(StateID::RelationShipState,ComponentType::TypeRelationShip);
}

void AddNodeState::mousePressEvent(Point position){
    string nodeName = this->graphicalPresentation->getText();
    string nodeType = stateToNodeTypeMap.get(stateID);
    this->graphicalPresentation->addNode(nodeType,nodeName,Point());
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
}

void AddNodeState::mouseMoveEvent(Point position){
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
}

void AddNodeState::mouseReleaseEvent(Point position){
    this->graphicalPresentation->switchState(StateID::PointerState);
}