#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

AttributeWidget::AttributeWidget(Component* component,QGraphicsItem* parent) : ComponentWidget(component,parent){
    this->setAcceptDrops(true);
}

AttributeWidget::~AttributeWidget(){
}

void AttributeWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawText(this->boundingRect(), Qt::AlignCenter,QString(this->component->getName().c_str()));
	painter->drawEllipse(this->boundingRect());
}

QRectF AttributeWidget::boundingRect() const{
     return QRectF(0, 0, 100, 50);
}