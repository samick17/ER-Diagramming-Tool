#include "TableWidget.h"
#include "Table.h"

TableWidget::TableWidget(Table* table) : table(table){
}

TableWidget::~TableWidget(){
}

QRectF TableWidget::boundingRect() const{
    return this->rect;
}

void TableWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
}