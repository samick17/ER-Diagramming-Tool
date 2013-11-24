#pragma once

#include "HashMap.h"
#include <QAction>
#include "QActionData.h"

class GraphicalUI;

class QActionMap{
public:
    QActionMap(GraphicalUI* graphicalUI);
    ~QActionMap();

    QAction* getQAction(unsigned int index);
private:
    void putQAction(QActionData qActionData,GraphicalUI* graphicalUI);
    HashMap<unsigned int,QAction*> actionMap;
};