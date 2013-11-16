#include "PreviewWidget.h"
#include "GraphicalPresentation.h"
#include "QPainter.h"

PreviewWidget::PreviewWidget(GraphicalPresentation* graphicalPresentation) : BaseWidget(graphicalPresentation){
}

PreviewWidget::~PreviewWidget(){
}

QPainterPath PreviewWidget::shape() const{
    QPainterPath path;
    QPolygonF line;
    line<<this->sourcePoint<<this->targetPoint;
    path.addPolygon(line);

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