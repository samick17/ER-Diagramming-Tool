#include "ConnectorWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <algorithm>

ConnectorWidget::ConnectorWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(graphicalPresentation,parent){
}

ConnectorWidget::~ConnectorWidget(){
}

void ConnectorWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawLine(this->sourcePoint,this->targetPoint);
    painter->drawText(this->rect, Qt::AlignCenter,QString(this->text.c_str()));
    this->drawSelectedFrame(painter);
}

void ConnectorWidget::setConnectionPoint(QPointF sourcePoint,QPointF targetPoint){
    int left = min(sourcePoint.x(),targetPoint.x());
    int top = min(sourcePoint.y(),targetPoint.y());
    this->rect = QRectF(left,top,abs(sourcePoint.x()-targetPoint.x()),abs(sourcePoint.y()-targetPoint.y()));
    this->sourcePoint = sourcePoint;
    this->targetPoint = targetPoint;
}