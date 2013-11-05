#include "NodeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "GraphicalPresentation.h"

using namespace Qt;

NodeWidget::NodeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(componentWidgetData,graphicalPresentation,parent){
}

NodeWidget::~NodeWidget(){
}

void NodeWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->rect,AlignCenter,QString(this->getText().c_str()));
}