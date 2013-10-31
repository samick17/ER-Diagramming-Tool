#include "EntityWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

EntityWidget::EntityWidget(Component* component,QGraphicsItem* parent) : ComponentWidget(component,parent){
    this->setAcceptDrops(true);
}

EntityWidget::~EntityWidget(){
}

void EntityWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawText(this->rect, Qt::AlignCenter,QString(this->component->getName().c_str()));
    painter->drawEllipse(this->rect);
}

QRectF EntityWidget::boundingRect() const{
    return this->rect;
}