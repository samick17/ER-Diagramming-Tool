#pragma once

#include <QGraphicsScene>
#include "IObserver.h"

class GraphicalUI;

class GUITableScene : public QGraphicsScene,public IObserver{
public:
    GUITableScene(GraphicalUI* graphicalUI);
    ~GUITableScene();

    void notify(Subject* subject);
};