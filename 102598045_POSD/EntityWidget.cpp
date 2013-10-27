#include <EntityWidget.h>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

EntityWidget::EntityWidget(Component* component,QGraphicsItem* parent) : ComponentWidget(component,parent){
	this->setAcceptDrops(true);
}

EntityWidget::~EntityWidget(){
}

void EntityWidget::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget){	
	painter->drawText(this->boundingRect(), Qt::AlignCenter,QString(this->component->getName().c_str()));
	painter->drawEllipse(0,0,100,50);
	if(mousePress)
		painter->drawRect(0,0,100,50);
}

QRectF EntityWidget::boundingRect() const{
     return QRectF(0, 0, 100, 50);
}