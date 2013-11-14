#include "NodeWidget.h"
#include <QPainter>

using namespace Qt;

NodeWidget::NodeWidget(Component* component,GraphicalPresentation* graphicalPresentation) : ComponentWidget(component,graphicalPresentation){
}

NodeWidget::~NodeWidget(){
}

void NodeWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->boundingRect(),AlignCenter,QString(this->getText().c_str()));
}