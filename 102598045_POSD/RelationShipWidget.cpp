#include "RelationShipWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

RelationShipWidget::RelationShipWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(graphicalPresentation,parent){
}

RelationShipWidget::~RelationShipWidget(){
}

QPainterPath RelationShipWidget::shape() const{
    QPainterPath path;
    QPolygon diamondPolygon;
    int left = rect.left();
    int top = rect.top();
    int right = rect.right();
    int bottom = rect.bottom();
    int centerX = rect.center().x();
    int centerY = rect.center().y();
    diamondPolygon<<QPoint(left,centerY)
                  <<QPoint(centerX,top)
                  <<QPoint(right,centerY)
                  <<QPoint(centerX,bottom)
                  <<QPoint(left,centerY);
    path.addPolygon(diamondPolygon);
    return path;
}

void RelationShipWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    painter->drawPath(this->shape());
    painter->drawText(this->rect, Qt::AlignCenter,QString(this->text.c_str()));
    this->drawSelectedFrame(painter);
}