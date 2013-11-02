#include "ConnectorWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

ConnectorWidget::ConnectorWidget(QGraphicsItem* parent) : ComponentWidget(parent){
}

ConnectorWidget::~ConnectorWidget(){
}

void ConnectorWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawEllipse(this->boundingRect());
}