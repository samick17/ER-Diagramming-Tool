#include "TableAttributeWidget.h"
#include <QPainter>
#include "Attribute.h"
#include "IconPath.h"
#include "WidgetDefaultSetting.h"
#include "Number.h"

using namespace Qt;

TableAttributeWidget::TableAttributeWidget(QPointF position,Attribute* attribute,int attributeType) : attribute(attribute){
    this->icon = QImage(IconPath::AttributeIcon[attributeType].c_str());
    //initial width
    double textWidth = this->attribute->getName().length()*WidgetDefaultSetting::TableUnitTextWidth;
    //initial icon rect
    this->iconRect = QRectF(position.x()+WidgetDefaultSetting::TableElementIconMargin,position.y()+WidgetDefaultSetting::TableElementIconMargin,WidgetDefaultSetting::TableElementIconWidth,WidgetDefaultSetting::TableElementIconHeight);
    //initial textrect
    this->textRect = QRect(position.x()+this->iconRect.width()+WidgetDefaultSetting::TableElementIconMargin*Number::Two,position.y(),textWidth,WidgetDefaultSetting::TableElementHeight);
    this->rect = QRectF(position.x(),position.y(),textWidth+this->iconRect.width()+WidgetDefaultSetting::TableElementIconMargin*Number::Two,WidgetDefaultSetting::TableElementHeight);
}

TableAttributeWidget::~TableAttributeWidget(){
}

QRectF TableAttributeWidget::boundingRect() const{
    return this->rect;
}

double TableAttributeWidget::getWidth(){
    return this->rect.width();
}

void TableAttributeWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));

    //draw Icon
    painter->drawImage(this->iconRect,this->icon);
    //draw Name
    painter->drawText(this->textRect,Qt::AlignVCenter,this->attribute->getName().c_str());
    painter->drawRect(this->rect);
}