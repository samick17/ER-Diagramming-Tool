#include "RelationShipWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

using namespace Qt;

RelationShipWidget::RelationShipWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation) : NodeWidget(componentWidgetData,graphicalPresentation){
}

RelationShipWidget::~RelationShipWidget(){
}

QPainterPath RelationShipWidget::shape() const{
    QPainterPath path;
    QPolygonF diamondPolygon;
    QPointF centerLeft = QPointF(this->rect.left(),this->rect.center().y());
    QPointF centerTop = QPointF(this->rect.center().x(),this->rect.top());
    QPointF centerRight = QPointF(this->rect.right(),this->rect.center().y());
    QPointF centerBottom = QPointF(this->rect.center().x(),this->rect.bottom());
    diamondPolygon<<centerLeft<<centerTop<<centerRight<<centerBottom<<centerLeft;
    path.addPolygon(diamondPolygon);
    return path;
}