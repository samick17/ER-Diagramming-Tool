#include "RelationShipWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

RelationShipWidget::RelationShipWidget(QRectF rect,QGraphicsItem* parent) : ComponentWidget(rect,parent){
}

RelationShipWidget::~RelationShipWidget(){
}

void RelationShipWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawEllipse(this->boundingRect());
}