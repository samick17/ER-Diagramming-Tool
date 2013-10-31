#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

ComponentWidget::ComponentWidget(QRectF rect,QGraphicsItem* parent) : rect(rect),QGraphicsItem(parent){
}

ComponentWidget::~ComponentWidget(){
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::move(QPointF position){
    this->setPos(position);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}