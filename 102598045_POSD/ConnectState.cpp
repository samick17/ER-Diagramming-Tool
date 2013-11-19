#include "ConnectState.h"
#include "ConnectorData.h"
#include "ComponentType.h"

ConnectState::ConnectState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

ConnectState::~ConnectState(){
}

void ConnectState::onCreate(){

}

void ConnectState::doMousePressEvent(Point position){
    ComponentData componentData = ComponentData(ComponentType::TypeConnector,"Preview","");
    ConnectorData* connectorData = new ConnectorData(componentData,position,position);
    this->graphicalPresentation->setComponentDataForPreview(connectorData);
}

void ConnectState::doMouseMoveEvent(Point position){
    ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
    ConnectorData* connectorData = static_cast<ConnectorData*>(componentData);
    connectorData->setTargetPoint(position);
}

void ConnectState::doMouseReleaseEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastReleasedComponent();
    this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
}