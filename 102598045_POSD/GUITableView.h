#pragma once

#include <QGraphicsView>
#include "IObserver.h"

class GraphicalPresentation;

class GUITableView : public QGraphicsView,public IObserver{
public:
    GUITableView(GraphicalPresentation* graphicalPresentation,QGraphicsScene* scene,QWidget* parent = NULL);
    ~GUITableView();

    void notify(Subject* subject);
private:
    GraphicalPresentation* graphicalPresentation;
};