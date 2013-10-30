#include "ConnectorWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

ConnectorWidget::ConnectorWidget(Component* component,QGraphicsItem* parent) : ComponentWidget(component,parent){
    this->setAcceptDrops(true);
}

ConnectorWidget::~ConnectorWidget(){
}

void ConnectorWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawText(this->boundingRect(), Qt::AlignCenter,QString(this->component->getName().c_str()));
    painter->drawEllipse(this->boundingRect());
}

QRectF ConnectorWidget::boundingRect() const{
     return QRectF(0, 0, 100, 50);
}