#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

AttributeWidget::AttributeWidget(QRectF rect,QGraphicsItem* parent) : ComponentWidget(component,parent){
}

AttributeWidget::~AttributeWidget(){
}

void AttributeWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    //painter->drawText(this->boundingRect(), Qt::AlignCenter,QString(this->component->getName().c_str()));
    painter->drawEllipse(this->boundingRect());
}