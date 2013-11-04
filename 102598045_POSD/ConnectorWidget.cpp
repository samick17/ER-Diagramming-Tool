#include "ConnectorWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <algorithm>

ConnectorWidget::ConnectorWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(componentWidgetData,graphicalPresentation,parent){
}

ConnectorWidget::~ConnectorWidget(){
}


void ConnectorWidget::doPaint(QPainter* painter){
    painter->drawLine(this->sourcePoint,this->targetPoint);
    painter->drawText(this->rect,Qt::AlignHCenter,QString(this->getText().c_str()));
}

void ConnectorWidget::setConnectionPoint(QPointF sourcePoint,QPointF targetPoint){
    int left = min(sourcePoint.x(),targetPoint.x());
    int top = min(sourcePoint.y(),targetPoint.y());
    this->rect = QRectF(left,top,abs(sourcePoint.x()-targetPoint.x()),abs(sourcePoint.y()-targetPoint.y()));
    this->sourcePoint = sourcePoint;
    this->targetPoint = targetPoint;
}