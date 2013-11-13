#include "EntityWidget.h"
#include <QPainter>

using namespace Qt;

EntityWidget::EntityWidget(Component** component,GraphicalPresentation* graphicalPresentation) : NodeWidget(component,graphicalPresentation){
}

EntityWidget::~EntityWidget(){
}

QPainterPath EntityWidget::shape() const{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}

void EntityWidget::doUpdateWidget(){}