#include "TableAttributeWidget.h"
#include <QPainter>
#include "Attribute.h"
#include "IconPath.h"

using namespace Qt;

TableAttributeWidget::TableAttributeWidget(QPointF position,Attribute* attribute,int attributeType) : attribute(attribute){
    this->icon = QImage(IconPath::AttributeIcon[attributeType].c_str());
    //initial width
    double width = this->attribute->getName().length()*12;
    //initial icon rect
    this->iconRect = QRectF(position.x()+2,position.y()+2,20,20);
    //initial textrect
    this->textRect = QRect(position.x()+24,position.y(),width-12,28);
    this->rect = QRectF(position.x(),position.y(),12+width,28);
}

TableAttributeWidget::~TableAttributeWidget(){
}

QRectF TableAttributeWidget::boundingRect() const{
    return this->rect;
}

double TableAttributeWidget::getWidth(){
    return this->rect.width();
}

void TableAttributeWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));

    //draw Icon
    painter->drawImage(this->iconRect,this->icon);
    //draw Name
    painter->drawText(this->textRect,Qt::AlignVCenter,this->attribute->getName().c_str());
    painter->drawRect(this->rect);
}