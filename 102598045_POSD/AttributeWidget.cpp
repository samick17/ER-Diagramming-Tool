#include "AttributeWidget.h"
#include <QPainter>

using namespace Qt;

AttributeWidget::AttributeWidget(Component* component,GraphicalPresentation* graphicalPresentation) : NodeWidget(component,graphicalPresentation){
}

AttributeWidget::~AttributeWidget(){
}

QPainterPath AttributeWidget::shape() const{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

void AttributeWidget::doUpdateWidget(){
    //update IsUnderLine
}