#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include "Node.h"
#include "DialogSetting.h"
#include "GraphicalPresentation.h"

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
    stateToNodeTypeMap.put(StateID::AttributeState,ComponentType::TypeAttribute);
    stateToNodeTypeMap.put(StateID::EntityState,ComponentType::TypeEntity);
    stateToNodeTypeMap.put(StateID::RelationShipState,ComponentType::TypeRelationShip);
}

AddNodeState::~AddNodeState(){
}
//this function will be called from StateFactory right after constructed.
void AddNodeState::onCreate(){
    string nodeType = stateToNodeTypeMap.get(this->getStateID());
    ComponentData* componentData = new ComponentData(nodeType,WidgetDefaultSetting::PreviewWidgetID);
    this->graphicalPresentation->setComponentDataForPreview(componentData);
}

void AddNodeState::doMousePressEvent(Point position){
}

void AddNodeState::doMouseMoveEvent(Point position){
    ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
    componentData->setCenterPosition(position);
}

void AddNodeState::doMouseDragEvent(Point position){
}

void AddNodeState::doMouseReleaseEvent(Point position){
    ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
    string nodeType = componentData->getType();
    string nodeName = componentData->getName();

    this->graphicalPresentation->addNode(nodeType,nodeName,Point());
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
    this->graphicalPresentation->switchState(StateID::PointerState);
}