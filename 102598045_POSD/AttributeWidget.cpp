#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "GraphicalPresentation.h"

using namespace Qt;

AttributeWidget::AttributeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : NodeWidget(componentWidgetData,graphicalPresentation,parent){
}

AttributeWidget::~AttributeWidget(){
}

QPainterPath AttributeWidget::shape() const{
    QPainterPath path;
    path.addEllipse(this->rect);
    return path;
}