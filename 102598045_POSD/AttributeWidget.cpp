#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "GraphicalPresentation.h"

AttributeWidget::AttributeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(componentWidgetData,graphicalPresentation,parent){
}

AttributeWidget::~AttributeWidget(){
}

QPainterPath AttributeWidget::shape() const{
    QPainterPath path;
    path.addEllipse(this->rect);
    return path;
}

void AttributeWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->rect,Qt::AlignCenter,QString(this->getText().c_str()));
}