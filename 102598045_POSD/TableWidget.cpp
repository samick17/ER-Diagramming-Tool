#include "TableWidget.h"
#include <QPainter>
#include <QGraphicsScene>
#include "Table.h"
#include "StringUtil.h"
#include "TableAttributeWidget.h"
#include "AttributeType.h"
#include "WidgetDefaultSetting.h"

using namespace Qt;

TableWidget::TableWidget(Table* table) : table(table){
}

TableWidget::~TableWidget(){
}

QRectF TableWidget::boundingRect() const{
    return this->rect;
}

void TableWidget::updateWidget(unsigned int index){
    QPointF leftTop = QPointF(0,index*WidgetDefaultSetting::TableRowHeight);
    unsigned int attributeIndex = 0;
    double totalWidth = WidgetDefaultSetting::TableElementMargin;
    for each(Attribute* attribute in this->table->getAllAttributeMap()){
        QPointF position = QPointF(leftTop.x()+totalWidth,leftTop.y()+WidgetDefaultSetting::TableWidgetTop+WidgetDefaultSetting::TableElementMargin);
        int attributeType = this->table->getAttributeType(attribute);
        TableAttributeWidget* tableAttributeWidget = new TableAttributeWidget(position,attribute,attributeType);

        double currentWidth = tableAttributeWidget->getWidth();

        this->scene()->addItem(tableAttributeWidget);
        totalWidth += currentWidth+WidgetDefaultSetting::TableElementMargin;
        attributeIndex++;
    }
    this->rect = QRectF(leftTop,QSize(totalWidth,WidgetDefaultSetting::TableWidgetHeight));
    this->textRect = QRectF(this->rect.topLeft().x(),this->rect.topLeft().y()+WidgetDefaultSetting::TableElementMargin,this->table->getEntityName().length()*WidgetDefaultSetting::TableUnitTextWidth,WidgetDefaultSetting::TableTitleHeight);
    this->rowRect = QRectF(leftTop.x(),leftTop.y()+WidgetDefaultSetting::TableWidgetTop,totalWidth,WidgetDefaultSetting::TableWidgetHeight);
}

void TableWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    painter->drawText(textRect,table->getEntityName().c_str());
    painter->drawRect(this->rowRect);
}