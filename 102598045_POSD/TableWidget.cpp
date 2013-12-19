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

void TableWidget::updateWidget(unsigned int index){
    this->rect = QRectF(0,index*60,240,36);
}

void TableWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
	painter->drawText(QRectF(this->rect.topLeft().x(),this->rect.topLeft().y()-18,80,24),table->getEntityName().c_str());
    painter->drawRect(this->boundingRect());
}