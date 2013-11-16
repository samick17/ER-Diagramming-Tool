#include "AttributeWidget.h"
#include <QPainter>
#include "Attribute.h"

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
    Attribute* attribute = static_cast<Attribute*>(this->component);
    this->setUnderLine(attribute->isPrimaryKey());
}