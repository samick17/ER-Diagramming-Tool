#include "GUIScrollView.h"
#include "GraphicalPresentation.h"

GUIScrollView::GUIScrollView(QGraphicsScene* scene,QWidget* parent) : QGraphicsView(scene,parent){
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

GUIScrollView::~GUIScrollView(){
}