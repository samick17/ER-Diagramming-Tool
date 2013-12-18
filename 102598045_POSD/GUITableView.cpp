#include "GUITableView.h"
#include "GraphicalPresentation.h"

GUITableView::GUITableView(GraphicalPresentation* graphicalPresentation,QGraphicsScene* scene,QWidget* parent) : QGraphicsView(scene,parent),graphicalPresentation(graphicalPresentation){
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->graphicalPresentation->registerObserver(this);
}

GUITableView::~GUITableView(){
    this->graphicalPresentation->unregisterObserver(this);
}

void GUITableView::notify(Subject* subject){
    if(graphicalPresentation->getIsDisplayDBTable())
        this->show();
    else
        this->hide();
}