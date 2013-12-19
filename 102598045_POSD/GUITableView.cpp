#include "GUITableView.h"
#include "GraphicalPresentation.h"

GUITableView::GUITableView(GraphicalPresentation* graphicalPresentation,QGraphicsScene* scene,QWidget* parent) : GUIScrollView(scene,parent),graphicalPresentation(graphicalPresentation){
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