#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

using namespace Qt;

ComponentWidget::ComponentWidget(ComponentWidgetData componentWidgetData,GraphicalPresentation* graphicalPresentation) : graphicalPresentation(graphicalPresentation),componentWidgetData(componentWidgetData){
    Rect rect = componentWidgetData.getRect();
    this->rect = QRectF(rect.getPosition().getX(),rect.getPosition().getY(),rect.getSize().getWidth(),rect.getSize().getHeight());
    this->getComponent()->registerObserver(this);
    this->graphicalPresentation->registerObserver(this);
}

ComponentWidget::~ComponentWidget(){
    this->getComponent()->unregisterObserver(this);
    this->graphicalPresentation->unregisterObserver(this);
}

Component* ComponentWidget::getComponent(){
    return this->componentWidgetData.getComponent();
}

string ComponentWidget::getText(){
    return this->getComponent()->getName();
}

void ComponentWidget::setText(string text){
    return this->getComponent()->setName(text);
}

bool ComponentWidget::getIsUnderLined(){
    return this->componentWidgetData.getIsUnderLined();
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    string componentID = this->getComponent()->getID();
    this->graphicalPresentation->selectWidget(componentID);
}

void ComponentWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent){
}

void ComponentWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget){
    //set anti-aliasing & pen width
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(black,WidgetDefaultSetting::WidgetLineWidth));
    //set under Lined
    QFont font = painter->font();
    font.setUnderline(this->getIsUnderLined());
    painter->setFont(font);
    //draw select frame to highlight
    this->drawSelectedFrame(painter);
    //paint 
    painter->setBrush(Qt::white);
    this->doPaint(painter);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}

void ComponentWidget::notify(ISubject* subject){
    this->update();
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    string componentID = this->getComponent()->getID();
    if(this->graphicalPresentation->isSelected(componentID)){
        painter->setPen(QPen(darkGreen,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
        painter->drawPath(this->shape());
    }
}