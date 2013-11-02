#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

ComponentWidget::ComponentWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : graphicalPresentation(graphicalPresentation),QGraphicsItem(parent){
    this->rect = QRectF(0,0,WidgetDefaultSetting::Width,WidgetDefaultSetting::Height);
}

ComponentWidget::~ComponentWidget(){
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->graphicalPresentation->selectWidget(this);
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::setText(string text){
    this->text = text;
}

void ComponentWidget::setBoundingRect(QRectF rect){
    this->rect = rect;
}

void ComponentWidget::setPos(int positionX,int positionY){
    this->rect = QRectF(positionX,positionY,WidgetDefaultSetting::Width,WidgetDefaultSetting::Height);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isSelected(this)){
        painter->setPen(QPen(Qt::red, WidgetDefaultSetting::SelectedFrameWidth, Qt::DotLine));
        painter->drawRect(this->rect);
    }
}