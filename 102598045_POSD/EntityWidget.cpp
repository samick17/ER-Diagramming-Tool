#include "EntityWidget.h"

EntityWidget::EntityWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation) : NodeWidget(componentData,graphicalPresentation){
}

EntityWidget::~EntityWidget(){
}

QPainterPath EntityWidget::shape() const{
    QPainterPath path;
    path.addRect(this->boundingRect());
    return path;
}