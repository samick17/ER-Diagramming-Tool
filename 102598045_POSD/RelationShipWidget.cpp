#include "RelationShipWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

RelationShipWidget::RelationShipWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(componentWidgetData,graphicalPresentation,parent){
}

RelationShipWidget::~RelationShipWidget(){
}

QPainterPath RelationShipWidget::shape() const{
    QPainterPath path;
    QPolygon diamondPolygon;
    QPoint centerLeft = QPoint(this->rect.left(),this->rect.center().y());
    QPoint centerTop = QPoint(this->rect.center().x(),this->rect.top());
    QPoint centerRight = QPoint(this->rect.right(),this->rect.center().y());
    QPoint centerBottom = QPoint(this->rect.center().x(),this->rect.bottom());
    diamondPolygon<<centerLeft<<centerTop<<centerRight<<centerBottom<<centerLeft;
    path.addPolygon(diamondPolygon);
    return path;
}

void RelationShipWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->rect,Qt::AlignCenter,QString(this->getText().c_str()));
}