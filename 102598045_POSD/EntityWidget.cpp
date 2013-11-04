#include "EntityWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

EntityWidget::EntityWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(graphicalPresentation,parent){
}

EntityWidget::~EntityWidget(){
}

QPainterPath EntityWidget::shape() const{
    QPainterPath path;
    path.addRect(this->rect);
    return path;
}

void EntityWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
	painter->drawPath(this->shape());
    painter->drawText(this->rect, Qt::AlignCenter,QString(this->text.c_str()));
    this->drawSelectedFrame(painter);
}