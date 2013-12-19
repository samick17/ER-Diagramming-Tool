#pragma once

#include <QGraphicsItem>

class Attribute;

class TableAttributeWidget : public QGraphicsItem{
public :
    TableAttributeWidget(QPointF position,Attribute* attribute,int attributeType);
    ~TableAttributeWidget();

    QRectF boundingRect() const;
    double getWidth();
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
private:
    QRectF rect,iconRect,textRect;
    QImage icon;
    Attribute* attribute;
};