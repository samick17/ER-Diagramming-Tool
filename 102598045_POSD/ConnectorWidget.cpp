#include "ConnectorWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

ConnectorWidget::ConnectorWidget(QRectF rect,QGraphicsItem* parent) : ComponentWidget(rect,parent){
    this->setAcceptDrops(true);
}

ConnectorWidget::~ConnectorWidget(){
}

void ConnectorWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawEllipse(this->boundingRect());
}