#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"

ComponentWidget::ComponentWidget(QGraphicsItem* parent) : QGraphicsItem(parent){
    this->rect = QRectF(0,0,WidgetDefaultSetting::Width,WidgetDefaultSetting::Height);
}

ComponentWidget::~ComponentWidget(){
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::move(QPointF position){
    this->setPos(position);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}