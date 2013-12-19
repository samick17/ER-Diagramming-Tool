#include "TableWidget.h"
#include <QPainter>
#include <QGraphicsScene>
#include "Table.h"
#include "StringUtil.h"
#include "TableAttributeWidget.h"
#include "AttributeType.h"

using namespace Qt;

TableWidget::TableWidget(Table* table) : table(table){
}

TableWidget::~TableWidget(){
}

QRectF TableWidget::boundingRect() const{
    return this->rect;
}

void TableWidget::updateWidget(unsigned int index){
    QPointF leftTop = QPointF(0,index*60);
    unsigned int attributeIndex = 0;
    double totalWidth = 4;
    for each(Attribute* attribute in this->table->getAllAttributeMap()){
        QPointF position = QPointF(leftTop.x()+totalWidth,leftTop.y()+4);
        int attributeType = this->table->getAttributeType(attribute);
        TableAttributeWidget* tableAttributeWidget = new TableAttributeWidget(position,attribute,attributeType);

        double currentWidth = tableAttributeWidget->getWidth();

        this->scene()->addItem(tableAttributeWidget);
        totalWidth += currentWidth+4;
        attributeIndex++;
    }
    this->rect = QRectF(leftTop,QSize(totalWidth,36));
}

void TableWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    painter->drawText(QRectF(this->rect.topLeft().x(),this->rect.topLeft().y()-18,80,24),table->getEntityName().c_str());
    painter->drawRect(this->boundingRect());
}