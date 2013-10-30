#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

ComponentWidget::ComponentWidget(Component* component,QGraphicsItem* parent) : component(component),QGraphicsItem(parent){
    this->setAcceptDrops(true);
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
     return QRectF(0, 0, 100, 50);
}