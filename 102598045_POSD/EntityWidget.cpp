#include "EntityWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

EntityWidget::EntityWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(componentWidgetData,graphicalPresentation,parent){
}

EntityWidget::~EntityWidget(){
}

QPainterPath EntityWidget::shape() const{
    QPainterPath path;
    path.addRect(this->rect);
    return path;
}

void EntityWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->rect,Qt::AlignCenter,QString(this->getText().c_str()));
}