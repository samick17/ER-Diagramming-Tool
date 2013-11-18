#include "AttributeWidget.h"
#include <QPainter>
#include "Attribute.h"

using namespace Qt;

AttributeWidget::AttributeWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation) : NodeWidget(componentData,graphicalPresentation){
}

AttributeWidget::~AttributeWidget(){
}

QPainterPath AttributeWidget::shape() const{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
}

void AttributeWidget::doUpdateWidget(){
    this->setUnderLine(this->componentData->getIsUnderLine());
}