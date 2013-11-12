#include "NodeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "GraphicalPresentation.h"

using namespace Qt;

NodeWidget::NodeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation) : ComponentWidget(componentWidgetData,graphicalPresentation){
}

NodeWidget::~NodeWidget(){
}

void NodeWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->rect,AlignCenter,QString(this->getText().c_str()));
}