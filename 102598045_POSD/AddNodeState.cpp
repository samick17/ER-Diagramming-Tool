#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include <QInputDialog>
#include <QObject>
#include "DialogSetting.h"

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
    stateToNodeTypeMap.put(StateID::AttributeState,ComponentType::TypeAttribute);
    stateToNodeTypeMap.put(StateID::EntityState,ComponentType::TypeEntity);
    stateToNodeTypeMap.put(StateID::RelationShipState,ComponentType::TypeRelationShip);
}

void AddNodeState::mousePressEvent(QPointF position){
    string nodeName = this->getNodeName();
    if (!nodeName.empty()){
        string nodeType = stateToNodeTypeMap.get(stateID);
        this->graphicalPresentation->addNode(nodeType,nodeName,position);
    }
    this->graphicalPresentation->switchState(StateID::PointerState);
}

void AddNodeState::mouseMoveEvent(QPointF position){
}

void AddNodeState::mouseReleaseEvent(QPointF position){
}

string AddNodeState::getNodeName(){
    QString text = QInputDialog::getText(NULL,QString(DialogSetting::Title.c_str()),QString(DialogSetting::Text.c_str()),QLineEdit::Normal);
    return text.toStdString();
}