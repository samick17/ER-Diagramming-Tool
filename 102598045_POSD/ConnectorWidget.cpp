#include "ConnectorWidget.h"
#include <QPainter>
#include "Connector.h"

using namespace Qt;

ConnectorWidget::ConnectorWidget(Component* component,GraphicalPresentation* graphicalPresentation) : ComponentWidget(component,graphicalPresentation){
}

ConnectorWidget::~ConnectorWidget(){
}

QPainterPath ConnectorWidget::shape() const{
    QPainterPath path;
    QPolygonF line;
    QPointF leftTop = QPointF(this->boundingRect().left(),this->boundingRect().top());
    QPointF rightBottom = QPointF(this->boundingRect().right(),this->boundingRect().bottom());
    line<<leftTop<<rightBottom;
    path.addPolygon(line);
    return path;
}

void ConnectorWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->boundingRect(),AlignHCenter,QString(this->getText().c_str()));
}