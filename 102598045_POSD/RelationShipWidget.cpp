#include "RelationShipWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

RelationShipWidget::RelationShipWidget(Component* component,QGraphicsItem* parent) : ComponentWidget(component,parent){
    this->setAcceptDrops(true);
}

RelationShipWidget::~RelationShipWidget(){
}

void RelationShipWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawText(this->boundingRect(), Qt::AlignCenter,QString(this->component->getName().c_str()));
    painter->drawEllipse(this->boundingRect());
}

QRectF RelationShipWidget::boundingRect() const{
     return QRectF(0, 0, 100, 50);
}