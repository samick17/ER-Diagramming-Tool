#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"


AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
    stateToNodeTypeMap.put(StateID::AttributeState,ComponentType::TypeAttribute);
    stateToNodeTypeMap.put(StateID::EntityState,ComponentType::TypeEntity);
    stateToNodeTypeMap.put(StateID::RelationShipState,ComponentType::TypeRelationShip);
}

void AddNodeState::mousePressEvent(QPointF position){
    string nodeType = stateToNodeTypeMap.get(stateID);
	this->graphicalPresentation->addNode(nodeType,position);
}

void AddNodeState::mouseMoveEvent(QPointF position){
}

void AddNodeState::mouseReleaseEvent(QPointF position){
    this->graphicalPresentation->switchState(StateID::PointerState);
}