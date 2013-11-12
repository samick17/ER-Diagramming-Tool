#include "EntityWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

using namespace Qt;

EntityWidget::EntityWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation) : NodeWidget(componentWidgetData,graphicalPresentation){
}

EntityWidget::~EntityWidget(){
}

QPainterPath EntityWidget::shape() const{
    QPainterPath path;
    path.addRect(this->rect);
    return path;
}