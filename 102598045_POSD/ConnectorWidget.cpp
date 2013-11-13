#include "ConnectorWidget.h"
#include <QPainter>
#include "GraphicalPresentation.h"
#include "Connector.h"

using namespace Qt;

ConnectorWidget::ConnectorWidget(Component** component,GraphicalPresentation* graphicalPresentation) : ComponentWidget(component,graphicalPresentation){
}

ConnectorWidget::~ConnectorWidget(){
}

QPainterPath ConnectorWidget::shape() const{
    QPainterPath path;
    QPolygonF line;
    line<<sourcePoint<<targetPoint;
    path.addPolygon(line);
    return path;
}

void ConnectorWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->boundingRect(),AlignHCenter,QString(this->getText().c_str()));
}

void ConnectorWidget::doUpdateWidget(){}