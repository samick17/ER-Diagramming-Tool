#include "ComponentWidget.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "WidgetDefaultSetting.h"
#include "GraphicalPresentation.h"

using namespace Qt;

ComponentWidget::ComponentWidget(Component** component,GraphicalPresentation* graphicalPresentation) : graphicalPresentation(graphicalPresentation),component(component){
    Rect componentRect = (*component)->getRect();
    Point position = componentRect.getPosition();
    Size size = componentRect.getSize();
    this->text = (*component)->getName(); 
    this->componentID = (*component)->getID();
    this->rect = QRectF(position.getX(),position.getY(),size.getWidth(),size.getHeight());
    (*component)->registerObserver(this);
    this->graphicalPresentation->registerObserver(this);
}

ComponentWidget::~ComponentWidget(){
    (*component)->unregisterObserver(this);
    this->graphicalPresentation->unregisterObserver(this);
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

void ComponentWidget::updateWidget(){
    doUpdateWidget();
}

void ComponentWidget::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){
    this->graphicalPresentation->selectWidget(this->componentID);
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
    font.setUnderline(false);
    painter->setFont(font);
    //draw select frame to highlight
    this->drawSelectedFrame(painter);
    //paint
    painter->setBrush(Qt::white);
    painter->fillPath(this->shape(),painter->brush());
    this->doPaint(painter);
}

QRectF ComponentWidget::boundingRect() const{
    return this->rect;
}

void ComponentWidget::notify(ISubject* subject){
    this->update();
    this->updateWidget();
}

void ComponentWidget::drawSelectedFrame(QPainter* painter){
    if(this->graphicalPresentation->isSelected(this->componentID)){
        painter->setPen(QPen(darkGreen,WidgetDefaultSetting::SelectedFrameLineWidth,Qt::DotLine));
        painter->drawPath(this->shape());
    }
}