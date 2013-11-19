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
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    if(!sourceComponent)
        return;
    ComponentData componentData = ComponentData(ComponentType::TypeConnector,WidgetDefaultSetting::PreviewWidgetID);
    ConnectorData* connectorData = new ConnectorData(componentData,position,position);
    Rect rect = sourceComponent->getRect();
    connectorData->setPointPair(rect.getMinDistanceToRectPoint(Rect(position)));
    this->graphicalPresentation->setComponentDataForPreview(connectorData);
}

void ConnectState::doMouseMoveEvent(Point position){
}

void ConnectState::doMouseDragEvent(Point position){
    ComponentData* componentData = this->graphicalPresentation->getComponentDataForPreview();
    ConnectorData* connectorData = dynamic_cast<ConnectorData*>(componentData);
    if(connectorData){
        connectorData->setTargetPoint(position);
        Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
        Component* targetComponent = this->graphicalPresentation->getLastMovedComponent();
        Rect sourceRect = sourceComponent->getRect();
        Rect targetRect = Rect(position);
        if(targetComponent)
            targetRect = targetComponent->getRect();
        connectorData->setPointPair(sourceRect.getMinDistanceToRectPoint(targetRect));
    }
}

void ConnectState::doMouseReleaseEvent(Point position){
    Component* sourceComponent = this->graphicalPresentation->getLastPressedComponent();
    Component* targetComponent = this->graphicalPresentation->getLastReleasedComponent();
    this->graphicalPresentation->addConnection(sourceComponent,targetComponent);
}