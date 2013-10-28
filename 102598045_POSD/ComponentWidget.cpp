#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

ComponentWidget::ComponentWidget(Component* component,QGraphicsItem* parent) : component(component),QGraphicsItem(parent){
    this->mousePress = false;
    this->setAcceptDrops(true);
}

ComponentWidget::~ComponentWidget(){
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    mouseEvent->accept();
    offset = mouseEvent->pos();
    this->mousePress = true;
    qDebug()<<"press!"<<endl;
    update();
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    mouseEvent->accept();
    move(mapToParent(mouseEvent->pos() - offset));
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){        
    mouseEvent->accept();
    this->mousePress = false;
    qDebug()<<"release!"<<endl;
    update();
}

void ComponentWidget::move(QPointF position){
    this->setPos(position);
}

QRectF ComponentWidget::boundingRect() const{
     return QRectF(0, 0, 100, 50);
}