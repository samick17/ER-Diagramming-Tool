#include "AttributeWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "GraphicalPresentation.h"

AttributeWidget::AttributeWidget(GraphicalPresentation* graphicalPresentation,QGraphicsItem* parent) : ComponentWidget(graphicalPresentation,parent){
    this->isDisplayUnderLine = false;
}

AttributeWidget::~AttributeWidget(){
}

void AttributeWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){
    if(this->isDisplayUnderLine){
        QFont font = painter->font();
        font.setUnderline(true);
        painter->setFont(font);
    }
    painter->drawEllipse(this->rect);
    painter->drawText(this->rect, Qt::AlignCenter,QString(this->text.c_str()));
    this->drawSelectedFrame(painter);
}

void AttributeWidget::showUnderLine(bool isDisplayUnderLine){
    this->isDisplayUnderLine = isDisplayUnderLine;
}