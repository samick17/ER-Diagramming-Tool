#include "ConnectorWidget.h"
#include <QPainter>
#include "Connector.h"

using namespace Qt;

ConnectorWidget::ConnectorWidget(Component* component,GraphicalPresentation* graphicalPresentation) : ComponentWidget(component,graphicalPresentation){
    Connector* connector = static_cast<Connector*>(this->component);
    connector->updateRect();
    this->updateWidget();
}

ConnectorWidget::~ConnectorWidget(){
}

QPainterPath ConnectorWidget::shape() const{
    QPainterPath path;
    QPolygonF line;
    line<<this->sourcePoint<<this->targetPoint;
    path.addPolygon(line);
    return path;
}

void ConnectorWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->boundingRect(),AlignHCenter,QString(this->getText().c_str()));
}

void ConnectorWidget::doUpdateWidget(){
    Connector* connector = static_cast<Connector*>(this->component);
    Component* firstComponent = connector->getFirstConnectedNode();
    Component* secondComponent = connector->getSecondConnectedNode();
    if(!firstComponent && !secondComponent)
        return;
    Point sourcePosition = firstComponent->getRect().getCenterPosition();
    this->sourcePoint = QPointF(sourcePosition.getX(),sourcePosition.getY());
    Point targetPosition = secondComponent->getRect().getCenterPosition();
    this->targetPoint = QPointF(targetPosition.getX(),targetPosition.getY());
}