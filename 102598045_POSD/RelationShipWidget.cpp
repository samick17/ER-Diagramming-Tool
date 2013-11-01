#include "RelationShipWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

RelationShipWidget::RelationShipWidget(QRectF rect,QGraphicsItem* parent) : ComponentWidget(rect,parent){
}

RelationShipWidget::~RelationShipWidget(){
}

void RelationShipWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
	painter->drawPolygon(getDiamondPolygon(this->boundingRect()));
	painter->drawText(this->boundingRect(), Qt::AlignCenter,QString("test"));
}

QPolygon RelationShipWidget::getDiamondPolygon(QRectF rect){
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
                  <<QPoint(centerX,bottom);
    return diamondPolygon;
}