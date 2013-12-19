#pragma once

#include "GUIScrollView.h"
#include "IObserver.h"

class GraphicalPresentation;

class GUITableView : public GUIScrollView,public IObserver{
public:
    GUITableView(GraphicalPresentation* graphicalPresentation,QGraphicsScene* scene,QWidget* parent = NULL);
    ~GUITableView();

    void notify(Subject* subject);
private:
    GraphicalPresentation* graphicalPresentation;
};