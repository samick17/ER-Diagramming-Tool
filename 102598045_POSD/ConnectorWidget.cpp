#include "ConnectorWidget.h"
#include "ConnectorData.h"

ConnectorWidget::ConnectorWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation) : ComponentWidget(componentData,graphicalPresentation){
    this->updateWidget();
}

ConnectorWidget::~ConnectorWidget(){
}

QPainterPath ConnectorWidget::shape() const{
    QPainterPath path;
    path.moveTo(this->sourcePoint);
    path.addEllipse(this->sourcePoint,WidgetDefaultSetting::WidgetLineWidth,WidgetDefaultSetting::WidgetLineWidth);
    path.lineTo(this->targetPoint);
    path.addEllipse(this->targetPoint,WidgetDefaultSetting::WidgetLineWidth,WidgetDefaultSetting::WidgetLineWidth);
    QPainterPathStroker painterPathStroker;
    painterPathStroker.setWidth(WidgetDefaultSetting::ConnectorWidth);
    path = painterPathStroker.createStroke(path);
    return path;
}

void ConnectorWidget::doUpdateWidget(){
    ConnectorData* connectorData = static_cast<ConnectorData*>(this->componentData);
    Point sourcePoint = connectorData->getSourcePoint();
    Point targetPoint = connectorData->getTargetPoint();
    this->sourcePoint = QPointF(sourcePoint.getX(),sourcePoint.getY());
    this->targetPoint = QPointF(targetPoint.getX(),targetPoint.getY());
}