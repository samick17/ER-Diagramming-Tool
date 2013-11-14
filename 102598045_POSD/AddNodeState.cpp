#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include "Node.h"

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
    stateToNodeTypeMap.put(StateID::AttributeState,ComponentType::TypeAttribute);
    stateToNodeTypeMap.put(StateID::EntityState,ComponentType::TypeEntity);
    stateToNodeTypeMap.put(StateID::RelationShipState,ComponentType::TypeRelationShip);
}

void AddNodeState::doMousePressEvent(Point position,Component* component){
    string nodeName = this->graphicalPresentation->getText();
    string nodeType = stateToNodeTypeMap.get(this->getStateID());
    this->graphicalPresentation->addNode(nodeType,nodeName,Point());
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
}

void AddNodeState::doMouseMoveEvent(Point position,Component* component){
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
}

void AddNodeState::doMouseReleaseEvent(Point position,Component* component){
    this->graphicalPresentation->switchState(StateID::PointerState);
}