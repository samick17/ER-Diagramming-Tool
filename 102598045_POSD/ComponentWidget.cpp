#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

using namespace Qt;

ComponentWidget::ComponentWidget(ComponentData* componentData,GraphicalPresentation* graphicalPresentation) : componentData(componentData),graphicalPresentation(graphicalPresentation){
    this->isUnderLine = false;
}

ComponentWidget::~ComponentWidget(){
}

void ComponentWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));
    //set under Lined
    QFont font = painter->font();
    font.setUnderline(this->getIsUnderLine());
    painter->setFont(font);
    //save currnet brush & set new brush
    QBrush brush = painter->brush();
    painter->setBrush(Qt::white);
    painter->fillPath(this->shape(),painter->brush());
    //paint
    this->doPaint(painter);
    //draw select frame to highlight
    painter->setBrush(brush);
    this->drawSelectedFrame(painter);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}

void ComponentWidget::doPaint(QPainter* painter){
    painter->drawPath(this->shape());
    painter->drawText(this->boundingRect(),AlignCenter,QString(this->getText().c_str()));
}

void ComponentWidget::updateWidget(){
    Rect componentRect = this->componentData->getRect();
    Point position = componentRect.getPosition();
    this->setText(this->componentData->getName());
    this->componentID = this->componentData->getID();
    this->setRect(QRectF(position.getX(),position.getY(),componentRect.getWidth(),componentRect.getHeight()));
    this->doUpdateWidget();
}

ComponentData* ComponentWidget::getComponentData(){
    return this->componentData;
}

string ComponentWidget::getText(){
	return this->text;
}

void ComponentWidget::setText(string text){
	this->text = text;
}

void ComponentWidget::setRect(QRectF rect){
	this->rect = rect;
}

bool ComponentWidget::getIsUnderLine(){
	return this->isUnderLine;
}

void ComponentWidget::setUnderLine(bool isUnderLine){
	this->isUnderLine = isUnderLine;
}

void ComponentWidget::doUpdateWidget(){
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isWidgetSelected(this->componentID)){
        painter->setPen(QPen(darkGreen,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
        painter->drawPath(this->shape());
    }
}