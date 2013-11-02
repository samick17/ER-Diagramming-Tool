#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

AttributeWidget::AttributeWidget(QGraphicsItem* parent) : ComponentWidget(parent){
}

AttributeWidget::~AttributeWidget(){
}

void AttributeWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawEllipse(this->boundingRect());
    painter->drawText(this->boundingRect(), Qt::AlignCenter,QString("test"));
}