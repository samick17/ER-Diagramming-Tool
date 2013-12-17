#include "TableWidget.h"
#include <QPainter>
#include <QGraphicsScene>
#include "Table.h"
#include "StringUtil.h"

TableWidget::TableWidget(Table* table) : table(table){
}

TableWidget::~TableWidget(){
}

QRectF TableWidget::boundingRect() const{
    return this->rect;
}

void TableWidget::updateWidget(){
    int index = this->scene()->items().indexOf(this);
    this->rect = QRect(0,index*120,200,36);
}

void TableWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
	int index = this->scene()->items().indexOf(this);
	painter->drawText(this->boundingRect(),StringUtil::intToString(index).c_str());
    painter->drawRect(this->boundingRect());
}