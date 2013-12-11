#include "ConnectState.h"
#include "ConnectorData.h"
#include "ComponentType.h"
#include "GraphicalPresentation.h"

ConnectState::ConnectState(int stateID,GraphicalPresentation* graphicalPresentation) : State(stateID,graphicalPresentation){
}

ConnectState::~ConnectState(){
}

void ConnectState::doMousePressEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    if(!sourceComponent || sourceComponent->isTypeOf<Connector>())
        return;
    //set preview connector
    ConnectorData* connectorData = new ConnectorData(WidgetDefaultSetting::PreviewWidgetID,StringSymbol::Empty,position,position);
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
    //cast to connectorData
    ConnectorData* connectorData = dynamic_cast<ConnectorData*>(componentData);
    if(!connectorData)
        return;
    //set connectorData Position
    connectorData->setTargetPoint(position);
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastMovedComponent();
    Rect sourceRect = sourceComponent->getRect();
    Rect targetRect = Rect(position,Size::Zero);
    //if target is connector, do nothing
    if(targetComponent && !targetComponent->isTypeOf<Connector>())
        targetRect = targetComponent->getRect();
    connectorData->setPointPair(sourceRect.getMinDistanceToRectPoint(targetRect));
    this->graphicalPresentation->notify();
}
//add connection
void ConnectState::doMouseReleaseEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastReleasedComponent();
    this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
}