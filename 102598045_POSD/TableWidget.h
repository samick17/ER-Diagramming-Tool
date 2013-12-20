#pragma once

#include <QGraphicsItem>

class Table;

class TableWidget : public QGraphicsItem{
public :
    TableWidget(Table* table);
    ~TableWidget();

    QRectF boundingRect() const;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget = 0);
    void updateWidget(unsigned int index);
private:
    QRectF rect,rowRect,textRect;
    Table* table;
};