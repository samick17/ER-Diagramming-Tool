#include "ConnectState.h"
#include "ConnectorData.h"
#include "ComponentType.h"
#include "GraphicalPresentation.h"

ConnectState::ConnectState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

ConnectState::~ConnectState(){
}

void ConnectState::onCreate(){
}

void ConnectState::doMousePressEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    if(!sourceComponent)
        return;
    //set preview connector
    ComponentData componentData = ComponentData(ComponentType::TypeConnector,ComponentType::TypeConnectorName,WidgetDefaultSetting::PreviewWidgetID);
    ConnectorData* connectorData = new ConnectorData(componentData,position,position);
    Rect rect = sourceComponent->getRect();
    pair<Point,Point> minDistainceToRectPoint = rect.getMinDistanceToRectPoint(Rect(position));
    connectorData->setPointPair(minDistainceToRectPoint);
    this->graphicalPresentation->setComponentDataForPreview(connectorData);
    this->graphicalPresentation->notify();
}

void ConnectState::doMouseMoveEvent(Point position){
}
//update preview connector
void ConnectState::doMouseDragEvent(Point position){
    ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
    ConnectorData* connectorData = dynamic_cast<ConnectorData*>(componentData);
    if(!connectorData)
        return;
    connectorData->setTargetPoint(position);
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastMovedComponent();
    Rect sourceRect = sourceComponent->getRect();
    Rect targetRect = Rect(position,Size::Zero);
    if(targetComponent)
        targetRect = targetComponent->getRect();
    connectorData->setPointPair(sourceRect.getMinDistanceToRectPoint(targetRect));
}
//add connection
void ConnectState::doMouseReleaseEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastReleasedComponent();
    this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
}