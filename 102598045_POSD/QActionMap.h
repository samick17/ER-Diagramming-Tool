#pragma once

#include "HashMap.h"
#include <QAction>
#include "QActionData.h"

class GraphicalUI;

class QActionMap{
public:
    QActionMap(GraphicalUI* graphicalUI);
    ~QActionMap();

    QAction* getQAction(string actionText);
private:
    HashMap<string,QAction*> actionMap;
    void putQAction(QActionData qActionData,GraphicalUI* graphicalUI);
};