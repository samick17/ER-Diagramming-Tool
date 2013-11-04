#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

ComponentWidget::ComponentWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : graphicalPresentation(graphicalPresentation),componentWidgetData(componentWidgetData),QGraphicsItem(parent){
    this->rect = QRectF(componentWidgetData.getPositionX(),componentWidgetData.getPositionY(),WidgetDefaultSetting::Width,WidgetDefaultSetting::Height);
}

ComponentWidget::~ComponentWidget(){
}

string ComponentWidget::getText(){
    return this->componentWidgetData.getText();
}

bool ComponentWidget::getIsUnderLined(){
    return this->componentWidgetData.getIsUnderLined();
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->graphicalPresentation->selectWidget(this);
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black,WidgetDefaultSetting::WidgetLineWidth));
    //set under Lined
    QFont font = painter->font();
    font.setUnderline(this->getIsUnderLined());
    painter->setFont(font);
    //paint
    this->doPaint(painter);
    //draw select frame to highlight
    this->drawSelectedFrame(painter);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isSelected(this)){
        painter->setPen(QPen(Qt::darkCyan,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
        painter->drawRect(this->rect);
    }
}