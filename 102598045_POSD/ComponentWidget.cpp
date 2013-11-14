#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"
#include <iostream>

using namespace Qt;

ComponentWidget::ComponentWidget(Component* component,GraphicalPresentation* graphicalPresentation) : graphicalPresentation(graphicalPresentation),component(component){
}

ComponentWidget::~ComponentWidget(){
}

string ComponentWidget::getText(){
    return this->text;
}

bool ComponentWidget::getIsUnderLine(){
    return this->isUnderLine;
}

string ComponentWidget::getComponentID(){
    return this->componentID;
}
/*
void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    Point position = Point(qPosition.x(),qPosition.y());
    this->graphicalPresentation->mousePressEvent(position,this->component);
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    Point position = Point(qPosition.x(),qPosition.y());
    this->graphicalPresentation->mouseMoveEvent(position,this->component);
	cout<<"widget mouse move"<<endl;
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
    QPointF qPosition = mouseEvent->scenePos();
    Point position = Point(qPosition.x(),qPosition.y());
    this->graphicalPresentation->mouseReleaseEvent(position,this->component);
}*/

Component* ComponentWidget::getComponent(){
    return this->component;
}

void ComponentWidget::updateWidget(){
    Rect componentRect = this->component->getRect();
    Point position = componentRect.getPosition();
    Size size = componentRect.getSize();
    this->text = this->component->getName(); 
    this->componentID = this->component->getID();
    this->rect = QRectF(position.getX(),position.getY(),size.getWidth(),size.getHeight());
    this->doUpdateWidget();
}

void ComponentWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));
    //set under Lined
    QFont font = painter->font();
    font.setUnderline(false);
    painter->setFont(font);
    QBrush brush = painter->brush();
    //paint
    painter->setBrush(Qt::white);
    painter->fillPath(this->shape(),painter->brush());
    this->doPaint(painter);
    //draw select frame to highlight
    painter->setBrush(brush);
    this->drawSelectedFrame(painter);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isSelected(this->componentID)){
        painter->setPen(QPen(darkGreen,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
		painter->drawRect(this->boundingRect());
    }
}