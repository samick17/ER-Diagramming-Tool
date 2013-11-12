#include "AddNodeState.h"
#include "StateID.h"
#include "ComponentType.h"
#include <QInputDialog>
#include <QObject>

AddNodeState::AddNodeState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
    stateToNodeTypeMap.put(StateID::AttributeState,ComponentType::TypeAttribute);
    stateToNodeTypeMap.put(StateID::EntityState,ComponentType::TypeEntity);
    stateToNodeTypeMap.put(StateID::RelationShipState,ComponentType::TypeRelationShip);
}

void AddNodeState::mousePressEvent(QPointF position){
    bool ok;
    QString text = QInputDialog::getText(NULL,QString(""),QString(""),QLineEdit::Normal,QString(""),&ok);
    if (ok && !text.isEmpty()){
        string nodeType = stateToNodeTypeMap.get(stateID);
        this->graphicalPresentation->addNode(nodeType,text.toStdString(),position);
    }
    this->graphicalPresentation->switchState(StateID::PointerState);
}

void AddNodeState::mouseMoveEvent(QPointF position){
}

void AddNodeState::mouseReleaseEvent(QPointF position){
}