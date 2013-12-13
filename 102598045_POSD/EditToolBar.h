#pragma once

#include <QToolBar>
#include "QActionMap.h"
#include "IObserver.h"

class GraphicalUI;
class GraphicalPresentation;

class EditToolBar : public QToolBar,public IObserver{
public:
    EditToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap);
    ~EditToolBar();

    void notify(Subject* subject);
private:
    GraphicalPresentation* graphicalPresentation;
};