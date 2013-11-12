#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "GraphicalPresentation.h"

using namespace Qt;

AttributeWidget::AttributeWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation) : NodeWidget(componentWidgetData,graphicalPresentation){
}

AttributeWidget::~AttributeWidget(){
}

QPainterPath AttributeWidget::shape() const{
    QPainterPath path;
    path.addEllipse(this->rect);
    return path;
}