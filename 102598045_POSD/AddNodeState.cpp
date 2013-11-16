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
    QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal);
    string nodeName = text.toStdString();
    this->graphicalPresentation->setText(nodeName);
}

void AddNodeState::doMousePressEvent(Point position){
    string nodeName = this->graphicalPresentation->getText();
    string nodeType = stateToNodeTypeMap.get(this->getStateID());
    this->graphicalPresentation->addNode(nodeType,nodeName,Point());
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
}

void AddNodeState::doMouseMoveEvent(Point position){
    Node* node = this->graphicalPresentation->getLastAddedNode();
    node->setCenterPosition(position);
}

void AddNodeState::doMouseReleaseEvent(Point position){
    this->graphicalPresentation->switchState(StateID::PointerState);
}