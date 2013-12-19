#pragma once

#include <QGraphicsView>

class GraphicalPresentation;

class GUIScrollView : public QGraphicsView{
public:
    GUIScrollView(QGraphicsScene* scene,QWidget* parent = NULL);
    ~GUIScrollView();
};