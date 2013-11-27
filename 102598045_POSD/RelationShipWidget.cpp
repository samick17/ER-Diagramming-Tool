#include "RelationShipWidget.h"

RelationShipWidget::RelationShipWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation) : NodeWidget(componentData,graphicalPresentation){
}

RelationShipWidget::~RelationShipWidget(){
}

QPainterPath RelationShipWidget::shape() const{
    QPainterPath path;
    QPolygonF diamondPolygon;
    QRectF rectangle = this->boundingRect();
    QPointF centerLeft = QPointF(rectangle.left(),rectangle.center().y());
    QPointF centerTop = QPointF(rectangle.center().x(),rectangle.top());
    QPointF centerRight = QPointF(rectangle.right(),rectangle.center().y());
    QPointF centerBottom = QPointF(rectangle.center().x(),rectangle.bottom());
    diamondPolygon<<centerLeft<<centerTop<<centerRight<<centerBottom<<centerLeft;
    path.addPolygon(diamondPolygon);
    return path;
}