#include "BaseWidget.h"
#include "GraphicalPresentation.h"
#include <QPainter>

using namespace Qt;

BaseWidget::BaseWidget(GraphicalPresentation* graphicalPresentation) : graphicalPresentation(graphicalPresentation){
    this->isUnderLine = false;
}

BaseWidget::~BaseWidget(){}

void BaseWidget::updateWidget(){
}

void BaseWidget::doUpdateWidget(){
}

void BaseWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));
    //set under Lined
    QFont font = painter->font();
    font.setUnderline(this->getIsUnderLine());
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

QRectF BaseWidget::boundingRect() const{
    return this->rect;
}

string BaseWidget::getText(){
    return this->text;
}

void BaseWidget::setText(string text){
    this->text = text;
}

void BaseWidget::setRect(QRectF rect){
    this->rect = rect;
}

bool BaseWidget::getIsUnderLine(){
    return this->isUnderLine;
}

void BaseWidget::setUnderLine(bool isUnderLine){
    this->isUnderLine = isUnderLine;
}

void BaseWidget::drawSelectedFrame(QPainter* painter){
}