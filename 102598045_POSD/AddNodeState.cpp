#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include "Node.h"
#include "DialogSetting.h"
#include <QInputDialog>

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
    ComponentData* componentData = new ComponentData(nodeType,"Preview","");
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
    bool isOK;
    QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal,"",&isOK);
    if(isOK){
        this->nodeName = text.toStdString();
        string nodeType = stateToNodeTypeMap.get(this->getStateID());
        this->graphicalPresentation->addNode(nodeType,this->nodeName,Point());
        Node* node = this->graphicalPresentation->getLastAddedNode();
        node->setCenterPosition(position);
    }
    this->graphicalPresentation->switchState(StateID::PointerState);
}