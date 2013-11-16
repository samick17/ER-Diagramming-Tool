#include "PreviewWidget.h"
#include "GraphicalPresentation.h"
#include "QPainter.h"

PreviewWidget::PreviewWidget(GraphicalPresentation* graphicalPresentation) : BaseWidget(graphicalPresentation){
}

PreviewWidget::~PreviewWidget(){
}

QPainterPath PreviewWidget::shape() const{
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

void PreviewWidget::updateWidget(){
    Point sourcePosition = this->graphicalPresentation->getPreviewSourcePoint();
    this->sourcePoint = QPointF(sourcePosition.getX(),sourcePosition.getY());
    Point targetPosition = this->graphicalPresentation->getPreviewTargetPoint();
    this->targetPoint = QPointF(targetPosition.getX(),targetPosition.getY());
}

void PreviewWidget::doUpdateWidget(){
}

void PreviewWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
}