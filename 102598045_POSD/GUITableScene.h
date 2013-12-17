#pragma once

#include <QGraphicsScene>

class GraphicalUI;

class GUITableScene : public QGraphicsScene{
public:
    GUITableScene(GraphicalUI* graphicalUI);
    ~GUITableScene();
};